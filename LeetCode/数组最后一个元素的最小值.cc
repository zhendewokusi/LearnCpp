class Solution {
public:
    long long minEnd(int n, int x) {
        long long ans = x;
        int i = 0, j = 0;
        n--;
        // j: n 当前比特位
        // i: ans 当前比特位
        while(n >> j) {
            if((ans >> i & 1) == 0) {
                ans |= (long long)(n >> j & 1) << i;
                j++;
            }
            i++;
        }
        return ans;
    }
};