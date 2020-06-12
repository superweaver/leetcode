#include "common.h"
class Solution {
  public:
    int bitwiseComplement(int N) {
        if (N == 0) {
            return 1;
        }
        int n = N;
        int bits = 0;
        while (N) {
            bits++;
            N >>= 1;
        }
        // cout << bits << endl;

        int mask = (1 << (bits)) - 1;
        // cout << mask << endl;
        n = (~n) & mask;
        return n;
    }
};

int main() {

    Solution s;

    return 0;
}
