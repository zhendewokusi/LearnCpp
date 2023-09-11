#include <vector>
using namespace std;
//快慢指针
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
      int slow_p = 0;
      if(nums.size() == 1) return 1;
      for(int fast_p = 0 ; fast_p < nums.size() ;++fast_p){
        if(nums[slow_p] != nums[fast_p]){
          slow_p++;
          nums[slow_p] = nums[fast_p];
        }
      }
        return slow_p+1;
    }
};