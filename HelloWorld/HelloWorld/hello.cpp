#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>

template <typename T>
void Print(T value)
{
    std::cout<< value << std::endl;
}

int main ()
{
    Print<float>(5);
    Print("666");
    Print(6.66);   
    // int a = glfwInit();
    // std::cout << a << std::endl;

    std::cin.get();
    
}