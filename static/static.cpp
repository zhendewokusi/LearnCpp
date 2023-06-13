// #include <iostream>

// struct Entity {
//      int x, y;

//     static void Print() { std::cout << x << "," << y << std::endl; }
// };

// // int Entity::x;
// // int Entity::y;

// int main() {
//     Entity e;
//     e.x = 2;
//     e.y = 3;

//     Entity e1;
//     e1.x = 5;
//     e1.y = 8;

//     Entity::Print();
//     Entity::Print();
//     std::cin.get();
//     return 0;
// }

// #include <iostream>

// class Entity {
// public:
//     static void Print() {
//         // int x; // 编译错误：无法从非静态成员函数中访问非静态成员
//         static int x = 0; // 正确：将局部变量定义为静态变量
//         std::cout << x++ << std::endl;
//     }
// };

// int main() {
//     Entity::Print(); // 输出0
//     Entity::Print(); // 输出1
//     Entity::Print(); // 输出2
//     return 0;
// }

#include <iostream>

void Print() {
    static int count = 0;  // 在函数内部定义静态局部变量
    count++;
    std::cout << "Count is: " << count << std::endl;
}

int main() {
    for (int i = 0; i < 3; i++) {
        Print();
    }
    return 0;
}
