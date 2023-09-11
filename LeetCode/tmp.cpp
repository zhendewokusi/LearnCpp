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


class Solution1 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return {searchLeftOrRightBound(nums, target, "left"), searchLeftOrRightBound(nums, target, "right")};
    }
private:
    int searchLeftOrRightBound(vector<int>& nums, int target, const string& bound) {
        int left = 0, right = nums.size() - 1;
        int res = -1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else if (nums[mid] > target) {
                right = mid - 1;
            }
            else {
                res = mid;
                if (bound == "left") {
                    right = mid - 1;
                }
                else if (bound == "right") {
                    left = mid + 1;
                }
                else {
                    // 异常处理段
                }
            }
        }
        return res;
    }
};