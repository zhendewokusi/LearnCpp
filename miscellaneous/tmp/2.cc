#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;
// int test1() {
//     auto upv =
//         std::make_unique<std::vector<int>>(std::initializer_list<int>{10, 20});
//     auto initlist = {10, 20};
//     auto spv = std::make_shared<std::vector<int>>(initlist);
    
//     std::cout << "std::unique_ptr elements: ";
//     for (const auto& element : *upv) {
//         std::cout << element << " ";
//     }
//     std::cout << std::endl;

//     std::cout << "std::shared_ptr elements: ";
//     for (const auto& element : *spv) {
//         std::cout << element << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }

// int test2() {
//     auto upv = std::make_unique<std::vector<int>>(10, 20);
//     auto spv = std::make_shared<std::vector<int>>(10, 20);

//     std::cout << "std::unique_ptr elements: ";
//     for (const auto& element : *upv) {
//         std::cout << element << " ";
//     }
//     std::cout << std::endl;

//     std::cout << "std::shared_ptr elements: ";
//     for (const auto& element : *spv) {
//         std::cout << element << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
// int main() {
//     // 创建 std::initializer_list 型别的对象
//     auto initlist = {10, 20};
//     auto spv = std::make_shared<std::vector<int>>(initlist);
//     test1();
//     test2();
// }

// class Solution {
// public:
//     void reverse(string& s, int start, int end){ //翻转，区间写法：左闭右闭 []
//         for (int i = start, j = end; i < j; i++, j--) {
//             swap(s[i], s[j]);
//         }
//     }

//     void removeExtraSpaces(string& s) {//去除所有空格并在相邻单词之间添加空格, 快慢指针。
//         int slow = 0;   
//         for (int i = 0; i < s.size(); ++i) { //
//             if (s[i] != ' ') { //遇到非空格就处理，即删除所有空格。
//                 if (slow != 0) s[slow++] = ' '; //手动控制空格，给单词之间添加空格。slow != 0说明不是第一个单词，需要在单词前添加空格。
//                 while (i < s.size() && s[i] != ' ') { //补上该单词，遇到空格说明单词结束。
//                     s[slow++] = s[i++];
//                 }
//             }
//         }
//         s.resize(slow); //slow的大小即为去除多余空格后的大小。
//     }

//     string reverseWords(string s) {
//         removeExtraSpaces(s); //去除多余空格，保证单词之间之只有一个空格，且字符串首尾没空格。
//         reverse(s, 0, s.size() - 1);
//         int start = 0; //removeExtraSpaces后保证第一个单词的开始下标一定是0。
//         for (int i = 0; i <= s.size(); ++i) {
//             if (i == s.size() || s[i] == ' ') { //到达空格或者串尾，说明一个单词结束。进行翻转。
//                 reverse(s, start, i - 1); //翻转，注意是左闭右闭 []的翻转。
//                 start = i + 1; //更新下一个单词的开始下标start
//             }
//         }
//         return s;
//     }
// };

class Solution {
public:
    int strStr(string haystack, string needle) {
    int index = 0;
    return index; 
    }
};