#include "common.h"
class Solution {
public:
  int reverse(int x) {
      // Assume we are dealing with an environment which could only store integers within the 32-bit
      // signed integer range it means you can't use a long to store x two operations:
      // 1) get the least significant digit of current x;
      // int lsd = x % 10; 2)
      // if (reversed * 10 + lsd) is within range, then do reversed = reversed * 10 + lsd;
      // how to check if (reversed * 10 + lsd)
      // is within range 
      // assume x is positive,
      // then if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && lsd > INT_MAX % 10)), overflow
      // assume x is negative,
      // then if (reversed < INT_MIN / 10 || (reversed == INT_MIN / 10 && lsd < INT_MIN % 10)), overflow
      //
      // INT_MAX % 10 = 7; (why? 7 < 10, 7 + 2^4 > 10, INT_MAX has all 1 from bit 0, to bit30) 
      // INT_MIN = -(INT_MAX + 1); then INT_MIN % 10 = -8;
      //
      if (x == INT_MIN) { // a special case
          return 0; // overflow
      }
      // now abs(x) <= INT_MAX
      int sign = x < 0 ? -1 : 1;
      x = x > 0 ? x : -x;
      const int c1 = INT_MAX / 10;
      const int c2 = INT_MAX % 10;
      int reversed = 0;
      while (x > 0) {
          int lsd = x % 10;
          if (reversed > c1 || (reversed == c1 && lsd > c2)) {
              return 0; // overflow
          } else {
              reversed = reversed * 10 + lsd;
          }
          x /= 10;
      }
      return sign > 0 ? reversed : -reversed;
  }
};

int main() {

	Solution s;

	return 0;
}
