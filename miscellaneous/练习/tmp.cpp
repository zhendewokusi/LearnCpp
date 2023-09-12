#include <memory>
#include <utility>

std::unique_ptr<int> up (new int(42));
std::shared_ptr<int> sp(std::move(up));