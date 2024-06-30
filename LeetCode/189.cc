#include <iostream>
#include <vector>
using namespace std;

/*有意思，想到了环状替代，但是没想出来具体代码*/

// class Solution {
// public:
//     void rotate(vector<int>& nums, int k) {
//         int n = nums.size();
//         k %= n;
//         int index = 0;
//         int next_index = index + k;
//         int stash_val = nums[index];

//         while(n--) {
//             nums[next_index] = stash_val;
//             index = next_index;
//             next_index = (index + k) % nums.size();
//             stash_val = nums[next_index];
//         }
//         return;
//     }
// };

// int main() {
// 	vector<int> tmp = {1,2,3,4,5,6,7};
// 	Solution s;
// 	s.rotate(tmp, 3);

// }

/*官方解答，下次再看*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        int count = gcd(k, n);
        for (int start = 0; start < count; ++start) {
            int current = start;
            int prev = nums[start];
            do {
                int next = (current + k) % n;
                swap(nums[next], prev);
                current = next;
            } while (start != current);
        }
    }
};