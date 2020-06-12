#include "common.h"

class Solution {
  public:
    int twoCitySchedCost(vector<vector<int>> &costs) {
        int result = 0;
        vector<int> delta_A;
        vector<int> delta_B;
        for (auto &v : costs) {
            if (v[0] < v[1]) {
                result += v[0];
                delta_A.push_back(v[1] - v[0]);
            } else if (v[0] > v[1]) {
                result += v[1];
                delta_B.push_back(v[0] - v[1]);
            } else {
                result += v[0];
            }
        }
        int n = costs.size() / 2; // half
        if (delta_A.size() <= n && delta_B.size() <= n) {
            return result;
        } else {
            if ((int)delta_A.size() > n) {
                sort(delta_A.begin(), delta_A.end());
                int terms = delta_A.size() - n;
                for (int i = 0; i < terms; ++i) {
                    result += delta_A[i];
                }
            } else {
                sort(delta_B.begin(), delta_B.end());
                int terms = delta_B.size() - n;
                for (int i = 0; i < terms; ++i) {
                    result += delta_B[i];
                }
            }
            return result;
        }
    }
};

int main() {

    Solution s;

    return 0;
}
