#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <bits/types/FILE.h>
#include <fcntl.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <exception>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>
#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"

class ClientTester {
    friend void RunClientTest(std::shared_ptr<ClientTester> tester);
    using NT = NetworkTest::NT;
    using Stub = NetworkTest::NT::Stub;
    using Result = NetworkTest::Result;
    using runtime_error = std::runtime_error;
    using Context = ::grpc::ClientContext;
    // 用于与服务器通信
    std::unique_ptr<Stub> stub;
    // 随机数字生成器
    std::default_random_engine re;
    // 字符类型随机生成器(Ascii)
    std::uniform_int_distribution<char> AsciiStringGenerator;
    // 字符类型随机生成器(二进制)
    std::uniform_int_distribution<char> BinStringGenerator;
    // 无符号32位整数随机数生成器
    std::uniform_int_distribution<uint32_t> LenGenerator;
    // 文件描述符,用于读取随机数字
    int fd;
    // 查询执行ID的测试状态
    void QueryStatus(uint64_t idx, Result& response) {
        // idx小于0则运行出错
        if (idx < 0)
            runtime_error("No Exist msg Idx<0\n");
        //
        if (idx <= SuccessMaxIdx) {
            response.set_id(SuccessMaxIdx);
            response.set_reason(Success);
            return;
        }
        Context context;
        NetworkTest::Query query;
        query.set_id(idx);
        auto res = stub->ResultQuery(&context, query, &response);
        if (!res.ok())
            runtime_error("Test Error,Please Retry!\n");
        if (response.reason() >= ErrorLevel)
            throw std::runtime_error(
                ErrorCode2Msg(static_cast<TestStatus>(response.reason())));
        if (response.reason() == Success)
            SuccessMaxIdx = std::max(SuccessMaxIdx, response.id());
    }
    // 向服务器发送测试信息
    void SendAnswer(const std::string& s) {
        SendSeq++;
        Context context;
        Result response;
        ::NetworkTest::Register answer;
        answer.set_content(s);
        auto res = stub->AnswerRegister(&context, answer, &response);
        if (!res.ok())
            runtime_error("Test Error,Please Retry!\n");
        if (response.reason() >= ErrorLevel)
            throw std::runtime_error(
                ErrorCode2Msg(static_cast<TestStatus>(response.reason())));
        if (response.reason() == Success)
            SuccessMaxIdx = std::max(SuccessMaxIdx, response.id());
    }
    //"当前"发送的测试信息的序列号
    uint32_t SendSeq = -1;
    // 已经成功处理的测试消息的最大序列号
    uint32_t SuccessMaxIdx = -1;
    // 将TestStatus类型的错误码转换为字符串类型
    static const char* ErrorCode2Msg(TestStatus s) noexcept {
        switch (s) {
            case Success:
                return "Success";
            case Wait:
                return "Wait For Msg";
            case WaitRPC:
                return "Wait For Test";
            case Diff:
                return "Msg is Error";
            case Unknow:
                return "Unknow Error";
            case ErrorLevel:
            case TestError:;
        }
        return "Tester is Error";
    }
    // 检查当前测试进度
    TestStatus Check() {
        using namespace std::chrono_literals;
        Result response;
        QueryStatus(SendSeq, response);
        if (response.id() == SendSeq && response.reason() == Success)
            return Success;
        std::this_thread::sleep_for(3s);
        return (response.id() == SendSeq && response.reason() == Success)
                   ? Success
                   : static_cast<TestStatus>(response.reason());
    }
    // 生成指定数量的 ASCII类型测试信息
    void genAsciiMsg(uint64_t size) {
        for (uint64_t i = 0; i < size; i++) {
            auto len = LenGenerator(re);
            auto ch = AsciiStringGenerator(re);
            std::string s(len, ch);
            SendAnswer(s);
            msgs->push(std::move(s));
        }
    }
    // 生成指定数量的二进制类型测试信息
    void genBinMsg(uint64_t size) {
        for (uint64_t i = 0; i < size; i++) {
            auto len = LenGenerator(re);
            std::string s;
            for (auto t = 0; t < len; t++)
                s.push_back(BinStringGenerator(re));
            SendAnswer(s);
            msgs->push(std::move(s));
        }
    }
    // 获取随机种子
    uint64_t getSeed() {
        fd = open("/dev/urandom", O_RDONLY);
        uint64_t seed;
        auto rc = read(fd, &seed, sizeof(seed));
        if (rc != sizeof(seed))
            throw runtime_error("read /dev/random failed");
        return seed;
    }

   public:
    // 初始化函数
    ClientTester(std::string addr)
        : stub(NT::NewStub(
              grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()))),
          re(getSeed()),
          msgs(std::make_shared<MsgBuf>()),
          AsciiStringGenerator(' ', '~'),
          BinStringGenerator(CHAR_MIN, CHAR_MAX),
          LenGenerator(0, 4096) {}
    // 该指针存储客户端发送的测试消息
    std::shared_ptr<MsgBuf> msgs;
    // 检查测试结果是否通过
    void FinishCheck() {
        auto res = Check();
        if (res == Success) {
            puts("Congratulations! You Pass The Test!");
            _exit(0);
        }
        printf("Sorry! You did not pass all Test. Reason:%s  :(\n",
               ErrorCode2Msg(res));
    }
};

// 用于执行用户端测试
void RunClientTest(std::shared_ptr<ClientTester> tester) {
    try {
        using namespace std::chrono_literals;
        tester->genAsciiMsg(1);
        std::this_thread::sleep_for(2s);
        auto reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 1\n");
        }
        tester->genAsciiMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 2\n");
        }
        tester->genAsciiMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 3\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 4\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 5\n");
        }
        tester->genBinMsg(1);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 6\n");
        }
        tester->genAsciiMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 7\n");
        }
        tester->genBinMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 8\n");
        }
        tester->genAsciiMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 9\n");
        }
        tester->genBinMsg(1024);
        reslut = tester->Check();
        if (reslut != Success) {
            printf("QAQ: Failed at 10\n");
        }
        printf("Success Pass All Test\n");
        _exit(0);
    } catch (...) {
        printf("Exception:\n");
    }
}
// 初始化客户端测试程序
std::shared_ptr<MsgBuf> InitTestClient(std::string addr) {
    try {
        auto tester = std::make_shared<ClientTester>(addr);
        // 创建线程用于执行测试程序
        auto test_thread = std::thread(RunClientTest, tester);
        test_thread.detach();
        return tester->msgs;
    } catch (std::exception& e) {
        // 如果异常
        printf("Exception: %s\n", e.what());
    }
    return nullptr;
}

struct Message {
    int msgID;
    int partID;
    std::string data;
};
class mess {
    int partid;
    int len;
};

class ClientClass {
   private:
    sockaddr_in addr;
    struct Message {
        uint32_t length;
        void* message;
    };
    int fd = -1;

   public:
    // 初始化
    ClientClass(char const* const ip, const int port) {
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            throw "fail creat socket";
            exit(1);
        }
        addr.sin_family = AF_INET;

        inet_pton(AF_INET, ip, &addr.sin_addr.s_addr);

        addr.sin_port = htons(PORT);
        if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            throw "connect";
            exit(1);
        }
    }
    ~ClientClass() { close(fd); }
    // 发送
    void SendMessage(const std::string&& message) {
        Message sendmessage;
        if (message.length() >= 0) {
            sendmessage.length = message.length();
        }
        if (send(fd, &sendmessage.length, sizeof(uint32_t), 0) < 0 ||
            send(fd, message.c_str(), message.length(), 0) < 0) {
            throw "send message";
            exit(1);
        }
        // std::cout << sendmessage.length << " " << message << std::endl;
    }
};

int main() {
    // Server 端的监听地址
    auto msg = InitTestClient("10.30.0.198:8888");
    // Put your code Here!

#if 1
    try {
        ClientClass client(ServerAddr, PORT);
        while (1) {
            std::string && tmp = msg->pop();
            std::cout << tmp << std::endl;
            client.SendMessage(std::move(tmp));
        }
    } catch (std::string  msg) {
        perror(msg.c_str());
        exit(1);
    }
#endif
}
