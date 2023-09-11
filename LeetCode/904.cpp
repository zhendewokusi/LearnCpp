#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int start = 0 ;     //起始指针
        int end = 0;        //终止指针
        int result = -1;
        std::unordered_map<int,int> storage;
        for(;end < fruits.size(); end++){
            storage[fruits[end]]++;
            while(storage.size() > 2){
                storage[fruits[start]]--;
                if(storage[fruits[start]]== 0)
                storage.erase(fruits[start]);
                start++;
            }
            result = max(result,end - start + 1);
            }
        
        return result == -1 ? 0 : result;
    }
};