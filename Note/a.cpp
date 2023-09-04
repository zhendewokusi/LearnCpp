#include <atomic>
#include <initializer_list>
#include <iostream>
#include <list>
#include <string>

// std::atomic<int> ai1{0};
// std::atomic<int> ai2(0);

// class Widget {
//    private:
//     int x{0};
//     int y = 0;
//     // int z(0);
// };
// typedef void (*FP)(int,const std::string&);

using FP = void (*)(int, const std::string&);

template <typename T>
struct MyAlloc {
    using value_type = T;
    T* allocate(std::size_t n) {
        std::cout << "Allocating memory for " << n << " elements" << std::endl;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* ptr, std::size_t n) {
        std::cout << "Deallocating memory for " << n << " elements"
                  << std::endl;
        ::operator delete(ptr);
    }
};

class Wine {};

template <typename T>
using MyAlloclist = std::list<T, MyAlloc<T>>;
MyAlloclist<int> lw;



void myFunction(int num, const std::string& str) {
    std::cout << "Number: " << num << std::endl;
    std::cout << "String: " << str << std::endl;
}

// int main() {
//     FP funcPtr =
//         myFunction;  // 创建 FP 类型的指针变量，并将其指向 myFunction 函数

//     int number = 42;
//     std::string message = "Hello, world!";
//     funcPtr(number, message);  // 通过指针变量调用 myFunction 函数

//     return 0;
// }

// using FP = void (*)(int, const std::string&);

void printMessage(int num, const std::string& message) {
    std::cout << "Number: " << num << ", Message: " << message << std::endl;
}

int main() {
    void (*funcPtr)(int, const std::string&) = printMessage;  // 将函数指针赋值给变量
    funcPtr(42, "Hello");  // 调用指向的函数

    return 0;
}