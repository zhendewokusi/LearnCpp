#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

int n, bag_size;

void func()
{
	vector<int> spaces(n,0);
	vector<int> value(n,0);
	// input
	for(int i=0;i < n;i++) {
		cin >> spaces[i];
	}
	for(int i=0;i < n;i++) {
		cin >> value[i];
	}

	vector<vector<int>> dp(spaces.size(),vector<int>(bag_size + 1,0));

	// init
	for(int j = spaces[0];j <= bag_size;j++) {
		dp[0][j] = value[0];
	}
	// 01背包
	for(int i = 1;i < spaces.size();i++) {
		for(int j = 0;j < bag_size;j++) {
			if(j < spaces[i])
				dp[i][j] = dp[i -1][j];
			else
				dp[i][j] = max(dp[i - 1][j] , dp[i - 1][j - spaces[i]] + value[i]);
		}
	}
	cout << dp[spaces.size() - 1][bag_size] << endl;
}

int main()
{
	while(cin >> n >> bag_size) {
		func();
	}
}