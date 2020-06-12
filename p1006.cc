#include "common.h"
class Solution {
  public:
    int clumsy(int N) {
        // N >=1 && N <= 10000
        // */+-
        int oprations = 0; //
        int result = 0;
        if (N <= 3) {
            return helper(N);
        } else {
            result += helper2(N);
            N -= 3;
            result += (N--);
            while (N >= 4) {
                result -= helper2(N);
                N -= 3;
                result += (N--);
            }
            result -= helper(N);
            return result;
        }
    }

  private:
    int helper(int n) {
        // for n = 1, 2, 3
        if (n == 3) {
            return 6;
        } else {
            return n;
        }
    }

    int helper2(int n) { return n * (n - 1) / (n - 2); }
};

int main() {

	Solution s;

	return 0;
}
