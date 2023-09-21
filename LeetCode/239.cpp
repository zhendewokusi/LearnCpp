#include <vector>
#include <deque>

using namespace std;
// //小丑了，题审错
// class Solution {
// public:
//     vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//         vector<int> result;
//         int sum = 0;
//         //窗口大小 大于 nums数组长度 
//         if(k >= nums.size()){
//             for(int i = 0 ; i < nums.size() ; i++){
//                 sum += nums[i];        
//             }
//             result.push_back(sum);
//             return result;
//         }
//         int i = 0;
//         for(int j = 0 ; j < nums.size() ; j++){
//             sum += nums[j];
//             if(j >= k - 1){
//                 result.push_back(sum);
//                 sum -= nums[i++];
//             }
//         }        
//         return result;
//     }
// };

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;    
        deque<int> window; // 使用双端队列来存储滑动窗口中的元素索引
        
        // 处理前 k 个元素
        for (int i = 0; i < k; i++) {
            while (!window.empty() && nums[i] >= nums[window.back()]) {
                window.pop_back();
            }
            window.push_back(i);
        }
        
        // 处理剩余元素
        for (int i = k; i < nums.size(); i++) {
            result.push_back(nums[window.front()]); // 当前窗口的最大值
            // 移除窗口左侧元素（如果超出窗口范围）
            if (!window.empty() && window.front() <= i - k) {
                window.pop_front();
            }
            // 添加新元素到窗口
            while (!window.empty() && nums[i] >= nums[window.back()]) {
                window.pop_back();
            }
            window.push_back(i);
        }
        
        result.push_back(nums[window.front()]); // 最后一个窗口的最大值
        
        return result;
    }
};
#include <iostream>


int main(){
    Solution s;
    vector<int> nums {1,3,-1,-3,5,3,6,7};
    vector<int>result = s.maxSlidingWindow(nums,3);
    for(auto& element : result ){
        std::cout << element << " " ;
    }
}