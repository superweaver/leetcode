#include "common.h"
class Solution {
public:
	int consecutiveNumbersSum(int N) {
		// assume sum of a , a+1, a+(k-1) is N
		// then (a + a +k-1)*k/2 ==N
		// (2a + k - 1) = 2N/k
		// k >= 1
		// a >= 1
		int count = 0;
		int n = 2 * N;
		int upper = (int)ceil((2*sqrt(2 * N + 1) - 1) / 2);
		for (int k = 1; k <= upper; k++) {
			if (n%k == 0) {
				int a2 = n / k + 1 - k;
				if (a2 > 0 & (a2 & 1) == 0) {
					count++;
					int a = a2 / 2;
					//cout << a << " : " << k << " = " << (k*(2*a + k -1) /2) <<  endl;
				}
			}
		}
		return count;
	}
};

int main() {

	Solution s;

	return 0;
}
