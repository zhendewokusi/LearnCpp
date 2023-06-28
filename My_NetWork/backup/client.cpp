// FTPClient.h

#include <iostream>
#include <fstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class FTPClient {
public:
    FTPClient(std::string host, int port);
    std::string sendCommand(std::string cmd);

private:
    int m_sock;
};

// FTPClient.cpp

FTPClient::FTPClient(std::string host, int port) : m_sock(0) {
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(host.c_str());
    serv_addr.sin_port = htons(port);
    connect(m_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
}

std::string FTPClient::sendCommand(std::string cmd) {
    send(m_sock, cmd.c_str(), cmd.size(), 0);
    char buf[1024];
    int n = recv(m_sock, buf, sizeof(buf), 0);
    std::string resp(buf, n);
    return resp;
}

int main() {
    FTPServer server(1234);
    FTPClient client("127.0.0.1", 1234);

    // test USER command
    std::string resp = client.sendCommand("USER test\r\n");
    std::cout << resp;

    // test PASS command
    resp = client.sendCommand("PASS test\r\n");
    std::cout << resp;

    // test LIST command
    resp = client.sendCommand("LIST\r\n");
    std::cout << resp;

    // test GET command
    resp = client.sendCommand("GET file.txt\r\n");
    std::cout << resp;

    // test PUT command
    resp = client.sendCommand("PUT file.txt\r\n");
    std::cout << resp;

    return 0;
}