#include <stdio.h>
#include <memory>
#include <utility>

int main() {
    int n[10];
    int i = 0; 
    while (i < 10 && scanf("%d", &n[i]) != EOF) {
        i++; // 移动到数组的下一个位置
    }
    // 输出数组中的数据
    for (int j = 0; j < i; j++) {
        printf("%d ", n[j]);
    }

    return 0;
}

template<typename T,typename... Ts>
std::unique_ptr<T> make_unique(Ts&&...params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}