#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    void getNext(int* next, const string& s) {
        int j = 0;
        next[0] = 0;
        for(int i = 1; i < s.size(); i++) {
            while (j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            }
            if (s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
        
    }
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) {
            return 0;
        }
        int next[needle.size()];
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while(j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == needle.size() ) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};

int main()
{
    // string tmp = {"aabaabaafaabaab"};
    // int arr[22] = {0};
    // Solution s;
    // s.getNext(arr, tmp);
    // for(int element:arr){
    //     std::cout << element  << " " ;
    // }
    int a = 1;
    printf("%d %d %d %d %d",a++,++a,++a,++a,a++);
}