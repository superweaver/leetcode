#include "common.h"
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int diff = INT_MAX;
        vector<vector<int>> result;
        for (size_t i = 1; i < arr.size() ; ++i){
            int current_diff = arr[i] - arr[i-1];
            if (current_diff == diff) {
                result.push_back({arr[i-1], arr[i]});
            } else if (current_diff < diff) {
                diff = current_diff;
                result = {{arr[i-1], arr[i]}};
            }
        }
        return result;
    }
};

int main(){
    vector<int> arr = {3,8,-10,23,19,-4,-14,27};
    Solution s;
    auto r = s.minimumAbsDifference(arr);
    for(auto&v:r){
        cout << v[0] << " " << v[1] << endl;
    }
    return 0;
}
