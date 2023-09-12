#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n , vector<int>(n,0));
        int x_start = 0;
        int y_start = 0;
        int offset = 1;
        int count = 1;
        int loop = n/2;
        while(loop -- ){
            //上
            for(int j = y_start ; j < n - offset ; j++){
                matrix[x_start][j] = count++;
            }
            //右
            for(int i = x_start ; i < n - offset; i++){
                matrix[i][n - offset] = count++;
            }
            //下
            for(int j = n - offset ; j > offset-1 ; j--){
                matrix[n - offset][j] = count++;
            }
            //左
            for(int i = n - offset; i > offset-1 ; i--){
                matrix[i][offset-1] = count++;
            }
            x_start++;
            y_start++;
            offset++;
        }
        if(n % 2 == 1) matrix[n/2][n/2] = n;
        return matrix;
    }
};


int main()
{
    Solution  s;
    vector<vector<int>> matrix = s.generateMatrix(2);
}