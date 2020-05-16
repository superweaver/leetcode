#include "common.h"
//https://leetcode.com/problems/single-number-ii/discuss/43295/Detailed-explanation-and-generalization-of-the-bitwise-operation-method-for-single-numbers
//
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // find one number in nums appear p times, while others appear k time;
        //
        // k = 3, p = 1
        // need m = 2, so 2^m > 3;
        // prepare x2 and x1
        int x1 = 0, x2 = 0, mask = 0;
        // decompose k as binary
        // mask = ~(y2 & y1)
        // y_i = bit_i(k)*x_i
        // k = 3 = 0x11 
        // so y2 = x2, y1 = x1
        // mask = ~(x2 & x1)
        for (auto v :nums) {
            x2 ^= (x1 & v); // x2 becomes 1 when both x1 and v are 1
            x1 ^= v;        // x1 becomes 1 when v is 1
            // get new mask
            mask = ~(x2 & x1);
            x2 &= mask;
            x1 &= mask;
        }
        // xi is the number appered i times
        return x1;
        
    }
};

int main() {

	Solution s;

	return 0;
}
