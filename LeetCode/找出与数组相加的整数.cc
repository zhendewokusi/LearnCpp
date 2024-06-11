// 2
class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        ranges::sort(nums1);
        ranges::sort(nums2);
        // 倒着枚举是因为 nums1[i] 越大答案越小，第一个满足的就是答案
        for (int i = 2; i; i--) {
            int diff = nums2[0] - nums1[i];
            // 在 {nums1[i] + diff} 中找子序列 nums2
            int j = 0;
            for (int k = i; k < nums1.size(); k++) {
                if (nums2[j] == nums1[k] + diff && ++j == nums2.size()) {
                    return diff;
                }
            }
        }
        return nums2[0] - nums1[0];
    }
};

// 1
class Solution {
public:
    int addedInteger(vector<int>& nums1, vector<int>& nums2) {
        // ranges::sort(nums1);
        // ranges::sort(nums2);
        // return nums2[0] - nums1[0]; 
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        int n = nums1.size();
        return (sum2 - sum1) / n;
    }
};