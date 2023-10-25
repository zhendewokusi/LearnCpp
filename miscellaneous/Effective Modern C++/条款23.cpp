#include <alloca.h>
#include <algorithm>
#include <boost/type_index.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T>
void f(const T& param) {
    using boost::typeindex::type_id_with_cvr;
    using std::cout;

    // 显示T的型别
    cout << "T " << type_id_with_cvr<T>().pretty_name() << '\n';
    cout << "param " << type_id_with_cvr<decltype(param)>().pretty_name()
         << '\n';
}

template <typename T>
decltype(auto) move(T&& param) {
    using ReturnType = std::remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}

class Entity {
private:
    std::string value;

public:
    explicit Entity(const std::string tmp) : value(std::move(const_cast<std::string&>(tmp))) {}
};

void func(const Entity& left);
void func(Entity&& right);

template<typename T>
void func2(T&& param)
{
    // ...
    func(std::forward<T>(param));
    // ...
}


int main() {
    // int x = 42;
    // int& x_ref = x;
    // int&& rvalue_ref_1 = move(x);
    // int&& rvalue_ref_2 = move(x_ref);
    // return 0;
    std::string str("hello");
    // std::string i(std::move(sdfg));
    Entity e (str);
    func2(e);
    func2(std::move(e));
}

template<typename T>
void f(const T&& param);    // 右值引用

using namespace std;
template<class T , class Allocator = allocator<T>>
class vector{
public:
    template<class... Args>
    void emplace_back(Args&&... args);  // 万能引用
};

