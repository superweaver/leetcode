#include "common.h"
class Solution {
  public:
    vector<int> numMovesStones(int a, int b, int c) {
        vector<int> v = {a, b, c};
        sort(v.begin(), v.end());
        a = v[0];
        b = v[1];
        c = v[2];
        int min_step = 0;
        if (!(b == a + 1 && c == b + 1)) {
            int interval = min(b - a, c - b);
            if (interval <= 2) { // !!!
                min_step = 1;
                // for both 1   4 5 and 1 , 4 , 6,  one step is enough
            } else {
                min_step = 2;
            }
        }
        int max_step = c - a - 2;
        return {min_step, max_step};
    }
};

int main() {

    Solution s;

    return 0;
}
