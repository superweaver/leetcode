#include "common.h"
// https://leetcode.com/problems/bitwise-and-of-numbers-range/discuss/56729/Bit-operation-solution(JAVA)
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {

        // if least significant bit of m and n are not both 1, the that bit must be 0
        // if (m == n) then no need to & any more
        // if (m != n) then continue higher bit, the LSB for result is 0
        //
        // if least significant bit of m and n are both 1,
        //
        // if (m == n) then no need to & any more
        // if (m != n), that means in higher bit , there is difference
        // there is transition from 0 to 1
        // for example xxxx0yyyy1 to xxxx1yyyy1
        // then the lower value must have a transition from 1 to 0 later
        // so LSB for result is also 0
        if (m == 0) {
            return 0;
        }
        int shift = 0;
        while (m != n) {
            shift++;
            m >>= 1;
            n >>= 1;
        }
        return m << shift;
    }
};
int main() {

	Solution s;

	return 0;
}
