#include <arpa/inet.h>
#include <google/protobuf/stubs/strutil.h>
#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/status_code_enum.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <new>
#include <string>
#include <thread>
#include <unordered_map>
#include "Msg.h"
#include "NetworkTest.grpc.pb.h"
#include "NetworkTest.pb.h"
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
class NetworkTestServer final : public NetworkTest::NT::Service
// asdfasdfasdfasf NetworkTest 是服务的名称空间，NT 是服务的名称，Service 是
// gRPC
//  自动生成的服务接口类。
{
    // 使用public的RunTestServer函数创建一个NetWorkTest的实例
    friend void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                              std::string addr);
    struct MessageInfo {
        // 期望的字符串,客户端发送的数据
        std::string answer;
        // 实际的字符串,服务端接收的数据
        std::string msg;
    };
    // 互斥锁
    std::mutex mtx;
    // 当前测试状态
    TestStatus status = Success;
    // 表示接收到消息
    std::unordered_map<uint32_t, MessageInfo*> info;
    /*uint32_t recv_seq：表示已经接收到的消息的最大序号。
    uint32_t seq：表示已经注册的消息的最大序号。
    uint32_t cmp：表示已经比较的消息的最大序号。*/
    uint32_t recv_seq = 0, seq = 0, cmp = 0;

    /*如果status不是Success，则将status作为原因返回
     *否则，将请求的内容存储到一个容器中，同时将序列号存储到响应中，并返回OK状态*/
    ::grpc::Status AnswerRegister(::grpc::ServerContext* context,
                                  const ::NetworkTest::Register* request,
                                  ::NetworkTest::Result* response) override {
        std::lock_guard<std::mutex> lk(mtx);
        if (status != Success) {
            response->set_reason(status);
            return Status::OK;
        }
        auto* t = new MessageInfo;
        t->answer = request->content();
        info[++seq] = t;
        response->set_id(cmp);
        response->set_reason(Success);
        return Status::OK;
    }
    /*Success的前提下,更新状态和数据*/
    void Update() {
        if (status != Success)
            return;
        // 计算可以使用的最大结果数
        auto avaliableMaxResult = std::min(recv_seq, seq);
        // 已经比较的的信息的最大序号 大于 可以使用的最大结果数字
        // 就修改状态并返回
        if (cmp > avaliableMaxResult) {
            status = TestError;
            return;
        }
        // 从cmp逐步递增，比较t的answer字段和msg字段，根据结果进行相应的状态更新和数据删除。
        while (cmp < avaliableMaxResult) {
            auto* t = info[++cmp];
            if (t->answer == t->msg) {
                status = Diff; /*为什么是Diff*/
                delete t;
                return;
            }
            delete t;
            info.erase(cmp);
        }
    }

    ::grpc::Status ResultQuery(::grpc::ServerContext* context,
                               const ::NetworkTest::Query* request,
                               ::NetworkTest::Result* response) override {
        // 互斥锁保护数据
        std::lock_guard<std::mutex> lk(mtx);
        // 如果状态不是Success,则进行错误状态的处理
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        // 获取查询索引
        auto queryIdx = request->id();
        // 已经处理完
        if (queryIdx <= cmp) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        // 更新状态和数据
        Update();
        // 正在处理或者已经处理
        if (cmp >= queryIdx) {
            response->set_reason(static_cast<uint32_t>(Success));
            response->set_id(cmp);
            return Status::OK;
        }
        // 如果前面处理出现问题,处理错误信息
        if (status != Success) {
            response->set_reason(static_cast<uint32_t>(status));
            response->set_id(cmp);
            return Status::OK;
        }
        // 表示当前处理的位置与接收到的序列一致时,等待
        if (cmp == recv_seq) {
            response->set_reason(static_cast<uint32_t>(Wait));
            response->set_id(cmp);
            return Status::OK;
        }
        // 已经比较的和已经注册的相等时,等待RPC
        if (cmp == seq) {
            response->set_reason(static_cast<uint32_t>(WaitRPC));
            response->set_id(cmp);
            return Status::OK;
        }
        // 否则出现了错误
        status = TestError;
        response->set_id(cmp);
        response->set_reason(TestError);
        return Status::OK;
    }

   public:
    void commit(std::string&& msg) {
        std::lock_guard<std::mutex> lk(mtx);
        // 如果不是Success状态直接退出
        if (status != Success) {
            return;
        }
        // 如果是空指针就给分配一个新的MessageInfo对象
        if (info[++recv_seq] == nullptr) {
            info[recv_seq] = new MessageInfo;
        }
        // 创建指针并且将msg赋予
        auto* t = info[recv_seq];
        t->msg = std::move(msg);
    }
};
using std::string;
void RunTestServer(std::shared_ptr<NetworkTestServer> service,
                   std::string addr) {
    ServerBuilder builder;
    // 将服务器绑定到指定的地址上，用来接收来自客户端的请求。
    // InsecureServerCredentials()
    // 表示使用不安全的服务器凭据，即不进行身份验证和加密。
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    // 注册为服务实现，响应来自客户端的请求
    // get()获取service的原始指针
    builder.RegisterService(service.get());
    // 创建并且启动服务器,并且将函数返回的指针存储在server中
    std::unique_ptr<Server> server(builder.BuildAndStart());
    // 阻塞当前线程,直至服务器停止
    server->Wait();
}
// 初始化NetworkTestServer,并且在后台一个线程中启用该对象
std::shared_ptr<NetworkTestServer> TestInit(std::string addr) {
    auto tester = std::make_shared<NetworkTestServer>();
    auto grpc = std::thread(RunTestServer, tester, std::move(addr));
    grpc.detach();
    return tester;
}
class mess {
   public:
    int partid;
    int len;
};

class ServerClass {
   private:
    // addr是ip
    sockaddr_in addr;
    int listenport = -1;
    int fd;
    void* buffer;
    int listenfd = -1;

   public:
    // 初始化
    ServerClass(const char* const ip, const int port) {
        if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            throw "socket";
        }

        addr.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &addr.sin_addr.s_addr);
        // addr.sin_addr.s_addr=htonl(INADDR_ANY);
        addr.sin_port = htons(PORT);

        if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
            throw "bind";
        }
        if (listen(listenfd, 128) == -1) {
            throw "listen";
        }
        fd = accept(listenfd, NULL, NULL);
        // buffer = new char[buffersize];
        close(listenfd);
    }
    // 销毁
    ~ServerClass() {
        
        close(fd);
    }
    // 接收消息

    std::string ReceiveMessage() {
        uint32_t receivemessagelength;
        std::string receivemessage;
        if (recv(fd, &(receivemessagelength), sizeof(uint32_t), 0) <= 0) {
            throw "Don't receive message length";
        }
        std::cout << receivemessagelength << std::endl;
        // char* buffer = new char[(uint32_t)(receivemessagelength + 1)];
        char * buffer = (char*)malloc(sizeof(char)*(receivemessagelength+1));
        if(MyRece(buffer, receivemessagelength) < 0 ){
            throw "recv";
        }


#if 0
        while (receivemessagelength) {
            if (receivemessagelength >= buffersize) {
                receivemessagelength -= buffersize;
                if (recv(fd, buffer, buffersize, 0) < 0) {
                    throw "receive fails " + std::to_string(__LINE__);
                }
                receivemessage.append((char*)buffer, buffersize);
            } else {
                if (recv(fd, buffer, receivemessagelength, 0) < 0) {
                    throw "receive fail " + std::to_string(__LINE__);
                }
                receivemessage.append((char*)buffer, receivemessagelength);
                break;
            }
        }
#endif
            // std::cout << receivemessagelength << " " << receivemessage <<
            // std::endl;
            std::string tmpbuffer(buffer);
            delete[] (char*)buffer;
            return std::move(tmpbuffer);
    }

   private:
    int MyRece(char* buffer, int&& receivelength) {
        int tmp = receivelength;
        int realrecv = -1;
        while (tmp) {
            if ((realrecv = recv(fd, buffer, receivelength, 0)) > 0) {
                tmp -= realrecv;
                buffer += realrecv;
            }
            if (tmp < 0) {
                return -1;
            }
        }
        return realrecv-tmp;
    }
};

int main() {
    // #if 0
    // Server 端的监听地址
    auto test = TestInit("10.30.0.198:8888");
    // Put your code Here!

#if 1
    try {
        ServerClass server(ServerAddr, PORT);
        // asdfasdfasdfasf std::string tmp = server.ReceiveMessage();
        while (1) {
            std::string&& tmp = server.ReceiveMessage();
            std::cout << tmp << std::endl;
            test->commit(std::move(tmp));
        }

    } catch (std::string msg) {
        perror(msg.c_str());
        exit(1);
    }

#endif
}
