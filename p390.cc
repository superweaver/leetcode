#include "common.h"
class Solution {
public:
    int lastRemaining(int n)
    {
        if (n < 1) {
            return 0;
        }
        return helper(n);
    }

private:
    int helper(int n)
    {
        // assume f(n) = k, left to right;
        // then f(n) right to left is (n+1) - k
        // map 1.. n to 2*i (2, 4, ..., 2n)
        // we have f(2n+1) = f(2n) = 2*( f(n, right to left) = n+1 - k)
        // f(2n + 1) = f(2n) = 2 * (n + 1 - f(n));
        if (n == 1) {
            return 1;
        }
        else {
            n >>= 1;
            n <<= 1;
            // return 2 * ((n / 2)+1 - helper(n / 2));
            return n + 2 - 2 * helper(n / 2);
        }
    }
};



int main() {

	Solution s;

	return 0;
}
