#include <iostream>
#include <string>

using namespace std;

// 暴力破解字符串匹配函数
int bruteForceSearch(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();

    for (int i = 0; i <= textLength - patternLength; i++) {
        int j;

        // 逐个字符比较主串和模式串
        for (j = 0; j < patternLength; j++) {
            if (text[i + j] != pattern[j]) {
                break;  // 如果有不匹配的字符，跳出内循环
            }
        }

        // 如果内循环完整执行，表示找到匹配
        if (j == patternLength) {
            return i;  // 返回匹配的位置
        }
    }

    return -1; // 未找到匹配
}

int main() {
    string text = "This is a sample text for string matching.";
    string pattern = "sample";

    int result = bruteForceSearch(text, pattern);

    if (result != -1) {
        cout << "Pattern found at position: " << result << endl;
    } else {
        cout << "Pattern not found in the text." << endl;
    }

    return 0;
}
