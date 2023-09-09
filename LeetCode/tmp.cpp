#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int search(vector<int>& nums, int target) 
    {
        int left=0,right=nums.size()-1;
        while(left<=right)
        {
            int pos=(left+right)/2;
            if(nums[pos]==target)
                return pos;
            else if(nums[pos]>target)
                right=pos-1;
            else
                left=pos+1;
        }
        return -1;
    }
};

