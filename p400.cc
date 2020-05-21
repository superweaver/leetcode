#include "common.h"

class Solution {
public:
    int findNthDigit(int n)
    {
        // n >= 1
        if (n <= 9) {
            return n;
        }
        int baseLen = 1;
        int numsInRange = 9;
        int sum = numsInRange * baseLen;
        baseLen++;
        numsInRange *= 10;

        //while (sum + baseLen * numsInRange < n) {
        while ((n - sum) / baseLen > numsInRange
         || ((n - sum) / baseLen == numsInRange && ( n - sum - baseLen * numsInRange > 0))) {
            sum += baseLen * numsInRange;
            baseLen++;
            numsInRange *= 10;
        }
        n -= sum;
        n -= 1;
        int start = pow(10, baseLen - 1);
        int div = n / baseLen;
        int r = n % baseLen;
        start += div;
        // pick the r digit from left to right;
        for (int i = 0; i < baseLen - r - 1; ++i) {
            start /= 10;
        }
        // get the lsb
        return start - (start / 10) * 10;
    }
};


int main() {

	Solution s;

	return 0;
}
