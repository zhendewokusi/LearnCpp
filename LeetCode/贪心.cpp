// P 2216


// 我觉得答案的贪心算法证明不太对，我写写我的贪心算法证明如下：

// 将数组分为很多个数组对，从左到右依次处理能，因为对当前数组对的处理不影响之前已经处理好的数组。问题分解为子问题，对每个数组对执行全局最优操作。下面分别证明各种数组对的贪心操作是全局最优解。

// 情况一：处理ab

// （1）不处理 —— 贪心操作

// （2）删除一个，奇偶变换

// （删除ab两个的操作浪费两个删除，直接排除）

// 情况二：处理aa

// （1）删除一个，奇偶变换 —— 贪心操作

// （2）删除两个

// （不删除aa任何一个的操作是违法的，直接排除。）

// 先考虑情况二的贪心操作：

// 处理aa，执行操作（1），如果a后序数组不需要任何删除，累积删除1，绝对优于对aa执行操作（2）后累积删除大于等于2的情况（如果操作（2）后序数组无需删除，取等号）。

// 处理aa，执行操作（1），如果a后序数组需要在位置j进行删除处理，不考虑操作（2），则只会对数据进行删除一个的处理，累积删除2个，且奇偶变换。此时j位置后序数组与对aa执行操作（2）后的j位置后序数组情况相同，且后者此时累积删除大于等于2（如果操作（2）直到j位置没有任何删除操作，取等号）。所以操作（1）优于操作（2）。 综上，全局最优操作不需要操作（2），只需贪心操作（1）就能找到全局最优。

// 现在，处理操作只剩下3种。

// 情况一：对于ab

// （1）不处理 —— 贪心操作

// （2）删除一个，奇偶变换

// 情况二：对于aa：

// （1）删除一个，奇偶变换 —— 贪心操作

// 考虑情况一的贪心操作： 类似情况二的分析，情况一的全局最优操作不需要操作（2）。只需贪心操作（1）就可以实现全局最优。


#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;
int main(){
    const std::vector<int> data = {-1,1,5};
    const auto is_positive = [](const auto &x) {return x > 0};
    auto find_pos_it = std::find_if(
        data.begin(),
        data.end(),
        is_positive);
    // use first_pos_it
}

void loop_map_itams() {
    std::unordered_map<std::string, std::string> colors = {
        {"RED", "#FF0000"},
        {"GREEN","#00FF00"}
    };
    for(const auto&[name,hex]:colors) {
        std::cout << "name:" << name << ", hex :" << hex << '\n';
    }
}

class Solution {
public:
    vector<string> findHighAccessEmployees(vector<vector<string>> &access_times) {
        map<string, vector<int>> groups;
        for (auto &p: access_times) {
            string name = p[0], s = p[1];
            int t = stoi(s.substr(0, 2)) * 60 + stoi(s.substr(2));
            groups[name].push_back(t);
        }

        vector<string> ans;
        for (auto &[name, a]: groups) {
            sort(a.begin(), a.end());
            for (int i = 2; i < a.size(); i++) {
                if (a[i] - a[i - 2] < 60) {
                    ans.emplace_back(name);
                    break;
                }
            }
        }
        return ans;
    }
};


