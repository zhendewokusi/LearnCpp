#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int main() {
    std::array<int, 10> array;
    for (int j = 0; j < array.size(); ++j) {
        array[j] = j;
    }
    for (const int& i : array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::vector<int> entity(array.crbegin(),array.crend());
    for(const int & j : entity){
        std::cout << j << " ";
    } 
    std::fill(entity.begin(), entity.end(), 10);
    for(const int & i : entity){
        std::cout << i << " ";
    }
    return 0;
}
