#include "common.h"
class Solution {

  public:
    int countBinarySubstrings(const string &s) {

        int res = 0; // result

        int kprev = 0; // the length of previous '0' or '1'

        int k = 0;       // the length of current '0' or '1'
        char cur = s[0]; // current character
        for (auto c : s) {
            if (c == cur) {
                k++;
                continue;
            }
            // 00011111, then min(kprev, k) = 3
            res += min(kprev, k); // get the min length of 0 or 1

            kprev = k;
            k = 1;
            cur = c;
        }
        // last piece
        return res + min(kprev, k); // don't forget it.
    }
};

int main() {

    Solution s;

    return 0;
}
