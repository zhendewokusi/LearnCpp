#include <iostream>

void printstring(int str[],int n) {
    for (int i = 0; i < n; i++) {
        std::cout << str[i] << " ";
    }
    std::cout << std::endl;
}

void resverstr(int str[],int start,int end){
    while (start < end) {
        int tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}

int main() {
    int str[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9,
    };
    int n = sizeof(str) / sizeof(str[0]);
    printstring(str, n);
    std::cout  << "this is resever string" << std::endl;
    resverstr(str, 0, n-1);
    printstring(str, n);
    
}