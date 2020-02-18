#include "common.h"
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        unordered_set<int> cache;
        int zeros = 0;
        for (size_t i = 0; i < arr.size(); ++i){            
            zeros += (arr[i] == 0);
            cache.insert(arr[i]);
        }
        if (zeros >= 2){
            return true;
        }
        if (zeros){
            cache.erase(0);
        }
        for(auto d: cache){
            if (cache.count(d*2)){
                return true;
            }
        }
        return false;
    }
};

int main() {
    vector<int> arr{ -2, 0, 10, -19, 4, 6, -8 };
    Solution s;
	cout << s.checkIfExist(arr) << endl;
    return 0;
}
