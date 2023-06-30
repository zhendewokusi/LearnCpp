#if 0
#include <algorithm>
#include <iostream>
int MostFrequentElement(int arr[],int n){
    int hash[100] = {};
    int max_element = 0;
    int max_count = 0;
    
    for(int i=0;i<n;i++){
        hash[arr[i]] ++;
        if(hash[arr[i]] > max_count){
            max_count = hash[arr[i]];
            max_element = arr[i];
        }
    }
    // return *std::max_element(hash,hash+99);
    return max_element;
    // return max_count;
}

int main() {
    int arr[] = {40, 50, 30, 40, 50, 30, 30};
    std::cout << MostFrequentElement(arr, sizeof(arr)/sizeof(arr[0])) << std::endl;
}
#endif


#include <bits/stdc++.h>
using namespace std;

int mostFrequent(int arr[], int n)
{
	// Insert all elements in hash.
	unordered_map<int, int> hash;
	for (int i = 0; i < n; i++)
		hash[arr[i]]++;

	// find the max frequency
	int max_count = 0, res = -1;
	for (auto i : hash) {
		if (max_count < i.second) {
			res = i.first;
			max_count = i.second;
		}
	}

	return res;
}

// driver program
int main()
{
	int arr[] = {40,50,30,40,50,30,30 };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << mostFrequent(arr, n);
	return 0;
}
