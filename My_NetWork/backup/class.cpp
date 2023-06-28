class FileTransferServiceImpl final : public FileTransfer::Service {
  Status SendFile(ServerContext* context, const FileRequest* request,
                  FileResponse* response) override {
    // 对传输的数据进行处理，例如保存到文件或进行其他操作
    // ...

    response->set_success(true);
    return Status::OK;
  }
};