#include "common.h"
//https://leetcode.com/problems/reaching-points/discuss/114726/C%2B%2B-Simple-iterative.
//

class Solution {
  public:
    bool reachingPoints_leetcode(int sx, int sy, int tx, int ty) {
        while (tx >= sx && ty >= sy) {
            if (tx > ty) {
                if (sy == ty)
                    return (tx - sx) % ty == 0;
                tx %= ty;
            } else {
                if (sx == tx)
                    return (ty - sy) % tx == 0;
                ty %= tx;
            }
        }
        return false;
    }

      // my solution
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (true) {
            if ((tx == sx) && (ty == sy)) {
                return true;
            }
            if (tx <= 0 || ty <= 0)
                return false;
            if (tx == ty) {
                return false;
            }
            if (ty < sy || tx < sx) {
                return false;
            }

            if (tx < ty) {
                int n = (ty - sy) / tx;
                n = max(1, n);
                ty -= n * tx;
            } else {
                int n = (tx - sx) / ty;
                n = max(1, n);
                tx -= n * ty;
            }
        }
    }
};

int main() {

	Solution s;

	return 0;
}
