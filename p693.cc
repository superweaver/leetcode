#include "common.h"
class Solution {
public:
    bool hasAlternatingBits(int n) {
        // test if n has pattern : 10101...
		long ln = n;
		long test = (ln >> 1) + ln + 1;
		// test if it is power of 2
		return (test & (test - 1)) == 0;
	}
};

int main() {

	Solution s;

	return 0;
}
