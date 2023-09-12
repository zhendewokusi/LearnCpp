#include <iostream>

class Resource {
public:
    Resource() {
        std::cout << "Resource acquired" << std::endl;
    }

    ~Resource() {
        std::cout << "Resource destroyed" << std::endl;
    }
};

class CustomDestructor {
public:
    CustomDestructor() {
        std::cout << "CustomDestructor created" << std::endl;
    }

    ~CustomDestructor() {
        std::cout << "CustomDestructor destroyed" << std::endl;
    }

private:
    Resource* ptr;
};

int main() {
    CustomDestructor obj1; // 创建对象1
    CustomDestructor obj2(obj1); // 复制构造函数，编译错误，因为复制构造函数没有自动生成

    return 0;
}
