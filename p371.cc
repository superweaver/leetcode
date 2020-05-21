#include "common.h"

class Solution {
public:
    int getSum(int a, int b)
    {
        // bitwise summation
        // overflow ?
        // bit a + bit b
        // sum = a^b
        // carry = a&b // sign of a and b !!!  // -a = ~a + 1
        const int guard = 0x80000000;
        bool pos_a = (a >= 0);
        bool pos_b = (b >= 0);
        if (pos_a && pos_b) {
            int t = sumoftwo(a, b);
            if (t & guard) {
                return INT_MAX;
            } else {
                return t;
            }
        }
        if (!pos_a && pos_b ) {
            return sumoftwo(a, b);
        }
        if (!pos_b && pos_a ) {
            return sumoftwo(a, b);
        }
        if (!pos_b && !pos_a) {
            if (a == INT_MIN || b == INT_MIN) {
                return INT_MIN;
            } else {
                int t = sumoftwo(-a, -b);
                if (t & guard) {
                    return INT_MIN;
                } else {
                    return -t;
                }
            }
        }
    }
private:
    int sumoftwo(int a, int b) {
        while(b!= 0) {
            int carry = a & b;
            a ^= b;
            b = carry << 1;
        }
        return a;
    }
};


int main() {

	Solution s;

	return 0;
}
