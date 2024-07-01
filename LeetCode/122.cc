class Solution {
public:
    /*
        前n天的利润总和 = 前n-1天的利润总和 + 第n天的利润（添加一个参数表示当前天数）
        第n天的利润 {买进股票(-prices[n])，什么都不做(0)，卖出股票(+prices[n])}

        要求：买进股票和卖出股票的状态不能共存(添加一个参数表示当前状态)

        状态转移方程：
            卖出股票：dfs(n,0) = max(dfs(n-1,0),dfs(n-1,1) - prices[n])
            买入股票：dfs(n,1) = max(dfs(n-1,1),dfs(n-1,0) + prices[n])
        边界处理：
            dfs(-1,0) = 0 开始前总利润为 0
            dfs(-1,1) = INT_MIN / 2 最开始不可能持有股票
        开始：
            最后肯定要卖股票才能利益最大化
    */
    // int maxProfit(vector<int>& prices) {
    //     int n = prices.size();
    //     vector<array<int, 2>> memo(n, {-1, -1}); // -1 表示还没有计算过
    //     function<int(int, bool)> dfs = [&](int index, bool status) -> int {
    //         if (index == -1) return status ? INT_MIN / 2 : 0;
    //         int &res = memo[index][status];
    //         if (res != -1) return res; // 之前计算过
    //         // 选择最大值
    //         return status ? 
    //             res = max(dfs(index - 1, 1), dfs(index - 1, 0) - prices[index]) :
    //             res = max(dfs(index - 1, 0), dfs(index - 1, 1) + prices[index]);
    //     };
    //     return dfs(n - 1, 0);
    // }

    int maxProfit(vector<int>& prices) {
        int n = prices.size(), f[n+1][2];
        memset(f, 0, sizeof(f));
        f[0][1] = INT_MIN;
        for(int i = 0;i < n; ++i) {
            f[i+1][0] = max(f[i][0],f[i][1] + prices[i]);
            f[i+1][1] = max(f[i][1],f[i][0] - prices[i]);
        }
        return f[n][0];
    }
};
