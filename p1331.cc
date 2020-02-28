#include "common.h"
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        if (arr.empty()) {
            return {};
        }
        vector<pair<int, int>> A;
        int n = arr.size();
        for (int i = 0; i < n; ++i){
            A.push_back({arr[i], i});
        }
        sort(A.begin(), A.end());
        int index = 1;
        arr[A[0].second] = index;
        for (int i = 1; i < n; ++i){
            if (A[i].first == A[i-1].first){
                arr[A[i].second] = index;
            } else {
                arr[A[i].second] = ++index;
            }
        }
        return arr;
    }
};

int main() {

	Solution s;

	return 0;
}
