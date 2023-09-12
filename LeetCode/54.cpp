class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int m = matrix.size(); //m 为行
        int n = matrix[0].size();// m 为列
        //(x0,y0)是左上角坐标
        int x0 = 0;
        int y0 = 0;
        //(x1,y1)是右下角坐标
        int x1 = n-1;
        int y1 = m-1;
        int count = 0;
        while(x1 > x0 && y1 > y0){
            //上 
            for(int j = x0 ; j < x1 ; j++){
                result.push_back(matrix[y0][j]);
            }
            //右
            for(int i = y0 ; i < y1 ; i++ ){
                result.push_back(matrix[i][x1]);
            }
            //下
            for(int j = x1; j > x0 ;j--){
                result.push_back(matrix[y1][j]);
            }
            //左
            for(int i = y1; i > y0; i--){
                result.push_back(matrix[i][x0]);
            }
            x1--;
            x0++;
            y1--;
            y0++;
        }
        //处理列
        if(x0 == x1) {
            while(y0 <=y1){
                result.push_back(matrix[y0++][x0]);
            }
        }else if(y0 == y1){
            while(x0 <=x1){
                result.push_back(matrix[y0][x0++]);
            }
        }
        return result;
    }
};