#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
       int left = 0 ;
       int right = nums.size() - 1 ;
       while(left <= right){
           int middle = (right + left)/2;
           if (nums[middle] > target) right = middle - 1 ;
           else if (nums[middle] < target) left = middle +1 ;
           else if(nums[middle]  == target) return middle;
       }
       return (right + left)/2 +1 ; 
    }
};