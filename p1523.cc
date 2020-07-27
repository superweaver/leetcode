#include "common.h"
class Solution {
public:
  int countOdds(int low, int high) {
      // f(x) = the number of odd number from [0, x]
      // then f(x) = (x + 1) / 2
      // the ans = f(high) - f(low-1);
      return (high + 1) / 2 - (low) / 2;
  }
};

int main() {

	Solution s;

	return 0;
}
