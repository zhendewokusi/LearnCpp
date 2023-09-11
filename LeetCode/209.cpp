#include <vector>
using namespace std;
class Solution {
public:
// 时间复杂度 O(n)
// 空间复杂度 O(1)
    int minSubArrayLen(int target, vector<int>& nums) {
        int end = 0;
        int start = 0;
        int sum = 0;
        int result = INT_MAX;
        // int result = -1;
        int sonArrLenth = 0;
        for(;end < nums.size();++end){
            sum += nums[end];
            //如果符合条件
            while(sum >= target){
                sonArrLenth = end - start +1 ;
                sum -= nums[start++];
                result = result < sonArrLenth ? result : sonArrLenth; 
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};