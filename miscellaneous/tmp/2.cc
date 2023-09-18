#include <iostream>
#include <memory>
#include <vector>

int test1() {
    auto upv =
        std::make_unique<std::vector<int>>(std::initializer_list<int>{10, 20});
    auto initlist = {10, 20};
    auto spv = std::make_shared<std::vector<int>>(initlist);
    
    std::cout << "std::unique_ptr elements: ";
    for (const auto& element : *upv) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "std::shared_ptr elements: ";
    for (const auto& element : *spv) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}

int test2() {
    auto upv = std::make_unique<std::vector<int>>(10, 20);
    auto spv = std::make_shared<std::vector<int>>(10, 20);

    std::cout << "std::unique_ptr elements: ";
    for (const auto& element : *upv) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "std::shared_ptr elements: ";
    for (const auto& element : *spv) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
int main() {
    // 创建 std::initializer_list 型别的对象
    auto initlist = {10, 20};
    auto spv = std::make_shared<std::vector<int>>(initlist);
    test1();
    test2();
}