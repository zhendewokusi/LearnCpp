#if 0
Given an array, write functions to find the minimum and maximum elements in it.
#endif
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

/*查找容器最小元素*/
int GetMin(int arr[],int n){
    return *std::min_element(arr,arr+n);
}
int GetMax(int arr[],int n){
    return *std::max_element(arr,arr+n);
}
/*递归查找*/
int RecursionGetMin(int arr[],int n){
    return (n == 1) ? arr[0] : std::min(arr[0],RecursionGetMin(arr+1, n-1));
}
int RecursionGetMax(int arr[],int n){
    return (n == 1) ? arr[0] : std::max(arr[0],RecursionGetMax(arr+1, n-1));
}





#if 1
int main(){
    int arr[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
    int range = sizeof(arr)/sizeof(arr[0]);
    std::sort(arr,arr+range);
    std::cout << "Max :" << arr[range-1] << "Min :" << arr[0] << std::endl;
    std::cout << "Max :" << GetMax(arr, range) << "Min :"  << GetMin(arr, range) << std::endl;
    std::cout <<"Max :"<< RecursionGetMax(arr, range) << "Min :" << RecursionGetMin(arr, range) << std::endl;
    
}
#endif

