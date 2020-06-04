#include "common.h"
class Solution {
public:
  int nthMagicalNumber(int N, int A, int B) {
      //https://zxi.mytechroad.com/blog/math/leetcode-878-nth-magical-number/
    const int kMod = 1000000007;
    long l = 2;
    long r = static_cast<long>(1e9 * 4e5);
    int d = gcd(A, B);
    while (l < r) {
      long m = (r - l) / 2 + l;
      // nice :)
      if (m / A + m / B - m / (A * B / d) < N) {
          l = m + 1;
      } else {
          r = m;
      }
    }
    return l % kMod;
  }
private:
  int gcd(int a, int b) {
    if (a % b == 0) return b;
    return gcd(b, a % b);
  }
};

int main() {

	Solution s;

	return 0;
}
