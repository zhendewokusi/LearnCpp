#include <iostream>
#include <vector>


int two_part_search() {
    std::vector<int> arr = {1, 2, 3, 4, 5, 12, 2};
    int target = 4;
    int left = 0;
    int right = arr.size() - 1;
    // 如果是左闭右闭
    while (left <= right) {
        int middle = (left + right) / 2;
        if (arr[middle] == target) {
            return middle;
        } else if (arr[middle] > target) {
            right = middle - 1;
        } else if (arr[middle] < target) {
            left = middle + 1;
        }
    }
    return -1;
    // 如果是左闭右开
    while (left < right) {
        int middle = (left + right) / 2;
        if (arr[middle] == target)
            return middle;
        else if (arr[middle] > target) {
            right = middle;
        } else if (arr[middle < target]) {
            left = middle + 1;
        }
    }
    return -1;
}
