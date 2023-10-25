
#include <string>
#include <functional>

// Leetcode 2698
// 很厉害的题解qaq

using namespace std;
int PRE_SUM[1001];

int init = []() {
    for (int i = 1; i <= 1000; i++) {
        string s = to_string(i * i);
        int n = s.length();
        function<bool(int, int)> dfs = [&](int p, int sum) -> bool {
            if (p == n) { // 递归终点
                return sum == i; // i 符合要求
            }
            int x = 0;
            for (int j = p; j < n; j++) { // 枚举分割出从 s[p] 到 s[j] 的子串
                x = x * 10 + s[j] - '0'; // 子串对应的整数值
                if (dfs(j + 1, sum + x)) {
                    return true;
                }
            }
            return false;
        };
        PRE_SUM[i] = PRE_SUM[i - 1] + (dfs(0, 0) ? i * i : 0);
    }
    return 0;
}();

class Solution {
public:
    int punishmentNumber(int n) {
        return PRE_SUM[n];
    }
};