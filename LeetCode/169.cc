/* 摩尔投票 有意思*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res = 0;
        int votes = 0;
        for(const auto& ele : nums) {
            if(votes == 0)  res = ele;
            votes += res == ele ? 1 : -1;  
        }
        return res;
    }
};