#include "common.h"
// a math question
class Solution {
public:
    int reachNumber(int target) {
        // target >= 0
        if (target == 0) return 0;
        if (target < 0) {
            target = - target;
        }
        // assume we go right
        // s = k * (k + 1) / 2
        // if s == target, return k
        // if s < k, then next k = k + 1;
        // sp = s + k + 1;, assume sp > target
        // get diff = sp - target
        // if diff is even, then previous diff/2 can be flipped to shift properly
        // if diff is odd; go further step right
        // spp = s + k + 1 + k + 2
        // check if new diff is even, if yes, return new k, otherwise, continue, return k + 1;
        // diff/2  can be flipped in previous step
        // find the larget k, that k*(k+1) / 2 <= target
        // then decide k + 1 or k + 2;
        long t = target;
        long k = (sqrt(8 * t + 1) - 1) / 2.0;
        k--;
        long test = k * (k + 1);
        if (test < 2 * target) {
            k++;
        } else if (test == 2 * target) {
            return k;
        }
        test = k * (k + 1);
        if (test < 2 * target) {
            k++;
        } else if (test == 2 * target) {
            return k;
        }
        // now test > target
        test = k * (k + 1) / 2;
        if (((test - target) & 1) == 0) {
            // even;
            return k;
        } else {
            k++;
            test += k;
            if (((test-target) & 1) == 0) { // still need to test
                return k;
            } else {
                return k + 1;
            }
        }
    }
};


int main() {

	Solution s;

	return 0;
}
