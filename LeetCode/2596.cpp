#include <vector>
using namespace std;

class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        int hrose_x = 0;
        int hrose_y = 0;
        int total_step = grid.size() * grid[0].size();
        int arr[4] = {-2, -1, 1, 2};
        int count = 0;
        // 总步数
        for (int i = 0; i < total_step; i++) {
            // 每一步的八种情况
            for (int j = 0; j < 4; j++) {      // j是横坐标
                for (int k = 0; k < 4; k++) {  // k是纵坐标
                    int sum = arr[j] + arr[k];
                    switch (sum) {
                        case 3:
                        case -1:
                        case 1:
                        case -3:
                            if (hrose_x + arr[j] < 0 || hrose_x + arr[j] >= grid[0].size())
                                continue;
                            if (hrose_y + arr[k] < 0 || hrose_y + arr[k] >= grid.size())
                                continue;
                            if (grid[hrose_x + arr[j]][hrose_y + arr[k]] == 1 + count) {
                                hrose_x += arr[j];
                                hrose_y += arr[k];
                                count++;
                                break;
                            }
                            break;
                        default:
                            break;
                    }
                }
                if (count == total_step-1)
                    break;
            }
        }
        return count == total_step-1;
    }
};

int main() {
    vector<vector<int>> grid = {
        { 0,11,16,5,20 },
        { 17,4,19,10,15 },
        { 12,1,8,21,6 },
        { 3,18,23,14,9 },
        { 24,13,2,7,22 }
    };
    Solution s;
    return s.checkValidGrid(grid);
}