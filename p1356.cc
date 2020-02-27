#include "common.h"
class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        vector<vector<int>> buckets(33);        
        for(auto d : arr){
            buckets[count(d)].push_back(d);
        }
        vector<int> result;
        for (auto&v: buckets){
            if (!v.empty()){
                result.insert(result.end(), v.begin(), v.end());
            }
        }
        return result;        
    }
    private:
    int count(int i){
        int ones = 0;
        while(i){
            ones++;
            i &= (i-1);
        }
        return ones;
    }
};
