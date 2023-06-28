#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include "file_transfer.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using filetransfer::FileTransfer;
using filetransfer::FileRequest;
using filetransfer::FileResponse;

class FileTransferServiceImpl final : public FileTransfer::Service {
  Status SendFile(ServerContext* context, const FileRequest* request,
                  FileResponse* response) override {
    // 对传输的数据进行处理，例如保存到文件或进行其他操作
    // ...

    response->set_success(true);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  FileTransferServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}