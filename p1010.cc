#include "common.h"
class Solution {
  public:
    int numPairsDivisibleBy60(vector<int> &time) {
        vector<int> cache(60, 0);
        for (auto i : time) {
            cache[i % 60]++;
        }
        int result = 0;
        // special handling for i == 0 and i == 30
        result += (cache[0] - 1) * cache[0] / 2 + cache[30] * (cache[30] - 1) / 2;
        for (int i = 1; i < 30; ++i) {
            if (cache[i] && cache[60 - i]) {
                result += cache[i] *
                          cache[60 - i]; // !!! i can serve as both lower index and higher index
            }
        }
        return result;
    }
};

int main() {

    Solution s;

    return 0;
}
