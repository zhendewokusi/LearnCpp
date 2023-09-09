#include <gnu/stubs-32.h>
#include <stdio.h>
#include <stdlib.h>

// int main() {
//     int a[9] = {
//         1, 2, 3, 4, 5, 6, 7, 8, 9,
//     };
//     // 32位系统编译 所有的地址为4，64位 为8
//     printf("%lu\n", sizeof(a));  // 36 一个整形四个字节，九个元素
//     printf("%lu\n", sizeof(a + 0));  // 8 表示指针
//     printf("%lu\n", sizeof(*a));  // 4 a首元素地址，*a解引用首元素大小
//     printf("%lu\n", sizeof(a + 1));      // 8 a首元素地址加1还是地址
//     printf("%lu\n", sizeof(a[1]));       // 4 数组第二个元素
//     printf("%lu\n", sizeof(&a));         // 8 整个数组地址
//     printf("%lu\n", sizeof(&a + 1));     // 8  指向下一个数组的地址
//     printf("%lu\n", sizeof(&a[0]));      // 8 首元素地址
//     printf("%lu\n", sizeof(&a[0] + 1));  // 8 第二个元素2的地址
//     printf("%lu\n", sizeof(*&a));  // 36  &a整个数组地址 解引用为整个数组大小
//     return 0;
// }


// char* fun(){
    // char *b;
    // char b[100];
    // b = (char *)malloc(4);
    // *b = '1';
    // *(b+1) = '2';
    // *(b+2) = '3';
    // *(b+3) = '4';
    // free(b);
    // return b;
// }

// int main(){
//     printf("%s",fun());
// }