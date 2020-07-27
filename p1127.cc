#include "common.h"
class Solution {
  public:
    int numEquivDominoPairs(vector<vector<int>> &dominoes) {
        vector<int> count(81, 0);
        for (auto &p : dominoes) {
            if (p[1] < p[0]) {
                // (p[1]-1)*9 + (p[0]-1)
                count[p[1] * 9 + p[0] - 10]++;
            } else {
                count[p[0] * 9 + p[1] - 10]++;
            }
        }
        int result = 0;
        for (auto k : count) {
            if (k >= 2) {
                result += k * (k - 1) / 2;
            }
        }
        return result;
    }
};

int main() {

    Solution s;

    return 0;
}
