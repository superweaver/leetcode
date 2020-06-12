#include "common.h"
class Solution {
public:
  int smallestRepunitDivByK(int K) {
      if (!(K & 1)) {
          return -1;
      }
      unordered_set<int> remainder; // remainder whiah has appeared
      int k = 1;
      k %= K;
      int step = 1;
      remainder.insert(k);
      const int t = (10 + K) % K;
      while (true) {
          if (k == 0) {
              return step;
          }
          // sum = sum * 10 + 1
          // the remainder = (sum * (10%K)+ 1) % K = (k *(10%K) + 1) % K;
          k = (k * t + 1) % K;
          if (remainder.count(k)) {
              return -1;
          } else {
              remainder.insert(k);
              step++;
          }
      }
      return step;
  }
};


int main() {

	Solution s;

	return 0;
}
