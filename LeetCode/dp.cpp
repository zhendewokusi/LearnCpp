/* 时间复杂度 O(n) 空间复杂度 O(n)*/
#include <vector>
#include <functional>

using namespace std;
class Solution {
public:
int rob(vector<int>& nums) {
    int n = nums.size();
    vector<int> hash(n,-1);
    function<int(int)> dfs = [&](int index) ->int {
        if(index < 0)   return 0;
        // 选或者不选
            if(hash[index] == -1)
            hash[index] = max(dfs(index - 1),dfs(index - 2) + nums[index]);
        return hash[index];
        // return max(dfs(index - 1),dfs(index - 2) + nums[index]);
    };  
    return dfs(n-1);
}   

};