#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//第一版
//暴力破解

//问题: 如果出现重复元素,会输出多次,而正确只需要输出一次
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::vector<std::vector<int>> result;
        for(int i =0 ; i < nums.size() ; i++ ){
            for(int j = i ; j < nums.size();j++){
                for(int k = j ; k < nums.size();k++){
                    if(i != k && i!=j && j!= k && nums[i] + nums[j] + nums[k] == 0)
                   
                    result.push_back({nums[i],nums[j],nums[k]});
                }
            }
        }
        return result;
    }
};
//第二版
//解决:双指针,并且将数组排序,重复元素跳过
class Solution1 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::sort(nums.begin(),nums.end());
        for(int i= 0 ; i < nums.size(); i++){
            //找两个数加起来是这个数字的负数
            int add_two = -nums[i];
            //跳过重复元素
            if(i > 0 && nums[i] == nums[i-1]  ) continue;
            int left = i+1;             //左指针
            int right = nums.size()-1;  //右指针
            while(left < right){
                int sum = nums[left] + nums[right];
                if(sum == add_two){
                    result.push_back({nums[i],nums[left],nums[right]});
                    while(left < right && nums[left] == nums[left+1]) left++;
                    while(left < right && nums[right] == nums[right-1]) right--;
                    left++;
                    right--;

                }else if(sum < add_two){
                    left++;
                }else{
                    right--;
                }
            }
        }
        return result;
    }
};