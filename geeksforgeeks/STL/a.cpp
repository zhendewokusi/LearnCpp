#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 在指定位置插入单个元素
    auto it = numbers.begin() + 2;  // 在第三个位置之前插入元素
    numbers.insert(it, 100);

    // 在指定位置插入多个元素
    it = numbers.begin() + 4;  // 在第五个位置之前插入元素
    std::vector<int > tmp = {100,200,300};
    auto begin = tmp.begin();
    auto end = tmp.end();
    numbers.insert(it,begin,end);

    // 输出容器元素
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}