// FTPServer.h

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>

class FTPServer {
public:
    FTPServer(int port);
    void run();

private:
    void listenLoop();
    void handleConnection(int sock);
    void handleCommand(int sock, std::string cmd);
    void sendResponse(int sock, std::string resp);
    void sendFile(int sock, std::string filename);
    void receiveFile(int sock, std::string filename);

    int m_port;
    int m_listen_fd;
    std::mutex m_mutex;
    std::vector<std::thread> m_threads;
};

// FTPServer.cpp

FTPServer::FTPServer(int port) : m_port(port), m_listen_fd(0) {}

void FTPServer::run() {
    struct sockaddr_in serv_addr;
    m_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(m_port);
    bind(m_listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(m_listen_fd, 5);
    std::cout << "FTP server started at port " << m_port << std::endl;
    listenLoop();
}

void FTPServer::listenLoop() {
    while (true) {
        int conn_fd = accept(m_listen_fd, NULL, NULL);
        std::thread t(&FTPServer::handleConnection, this, conn_fd);
        m_threads.push_back(std::move(t));
    }
}

void FTPServer::handleConnection(int sock) {
    sendResponse(sock, "220 FTP server ready.\r\n");
    while (true) {
        char buf[1024];
        int n = recv(sock, buf, sizeof(buf), 0);
        if (n <= 0) {
            break;
        }
        std::string cmd(buf, n);
        handleCommand(sock, cmd);
    }
    close(sock);
}

void FTPServer::handleCommand(int sock, std::string cmd) {
    if (cmd.substr(0, 4) == "USER") {
        sendResponse(sock, "331 Password required for user.\r\n");
    } else if (cmd.substr(0, 4) == "PASS") {
        sendResponse(sock, "230 User logged in, proceed.\r\n");
    } else if (cmd.substr(0, 4) == "LIST") {
        sendResponse(sock, "150 Opening data connection.\r\n");
        std::string filename = "filelist.txt";
        std::thread t(&FTPServer::sendFile, this, sock, filename);
        t.join();
        sendResponse(sock, "226 Transfer complete.\r\n");
    } else if (cmd.substr(0, 3) == "GET") {
        std::string filename = cmd.substr(4, cmd.size() - 6);
        sendResponse(sock, "150 Opening data connection.\r\n");
        std::thread t(&FTPServer::sendFile, this, sock, filename);
        t.join();
        sendResponse(sock, "226 Transfer complete.\r\n");
    } else if (cmd.substr(0, 3) == "PUT") {
        std::string filename = cmd.substr(4, cmd.size() - 6);
        sendResponse(sock, "150 Opening data connection.\r\n");
        std::thread t(&FTPServer::receiveFile, this, sock, filename);
    }
}
