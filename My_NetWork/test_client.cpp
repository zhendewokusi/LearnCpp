#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include "file_transfer.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using filetransfer::FileTransfer;
using filetransfer::FileRequest;
using filetransfer::FileResponse;

class FileTransferClient {
 public:
  FileTransferClient(std::shared_ptr<Channel> channel)
      : stub_(FileTransfer::NewStub(channel)) {}

  bool SendFile(const std::string& content) {
    FileRequest request;
    request.set_content(content);

    FileResponse response;
    ClientContext context;

    Status status = stub_->SendFile(&context, request, &response);

    if (status.ok()) {
      return response.success();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return false;
    }
  }

 private:
  std::unique_ptr<FileTransfer::Stub> stub_;
};

int main(int argc, char** argv) {
  FileTransferClient client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));

  std::string content = "Hello, World!";
  bool success = client.SendFile(content);

  if (success) {
    std::cout << "File sent successfully" << std::endl;
  } else {
    std::cout << "File sending failed" << std::endl;
  }

  return 0;
}