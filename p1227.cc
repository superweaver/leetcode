#include "common.h"
class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
      return n == 1 ? 1 : 0.5;
	  // if n == 1, then p = 1.0;
	  // if n == 2, then p = 0.5 * 1 + 0.5 * 0
	  // assume f(n-1) = p
	  // then f(n) = p * 1 + (1 - p) * 0;
	  // f(n) = f(n-1);
	  // f(n) = f(2) = 0.5;
    }
};

int main() {

	Solution s;
	cout << s.nthPersonGetsNthSeat(1) << endl;
	cout << s.nthPersonGetsNthSeat(2) << endl;
	cout << s.nthPersonGetsNthSeat(1000) << endl;
	return 0;
}
