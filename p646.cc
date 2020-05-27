#include "common.h"
class Solution {
  public:
    struct PairCompare {
        bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
            if (a.second != b.second) {
                return a.second < b.second;
            } else {
                return a.first < b.first;
            }
        }
    } funcObj;

    int findLongestChain(vector<vector<int>> &pairs) {
        vector<pair<int, int>> input;
        for (auto &v : pairs) {
            input.push_back({v[0], v[1]});
        }
        // sort(input.begin(), input.end(), funcObj);
        sort(input.begin(), input.end(), PairCompare());
        if (input.empty()) {
            return 0;
        }
        int result = 1;
        int n = input.size();
        int pre = 0; // index of previous block
        for (int i = 1; i < n; ++i) {
            if (input[i].second == input[pre].second) {
                continue;
            }

            if (input[i].first > input[pre].second) {
                ++result;
                pre = i;
            }
        }
        return result;
    }
};

int main() {

    Solution s;

    return 0;
}
