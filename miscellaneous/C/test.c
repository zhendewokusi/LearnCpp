#include <stdio.h>

int myFunction(char *str, int num) {
    // 函数实现
    return num * 2;
}

int main() {
    // 声明一个函数指针，并初始化为指向myFunction的指针
    int (*h)(char *, int);
    h = myFunction;

    // 现在可以使用h来调用函数
    int result = (*h)("Hello", 1);
    printf("%d\n", result);

    return 0;
}
