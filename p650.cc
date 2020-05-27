#include "common.h"
class Solution {
  public:
    int minSteps(int n) {
        // assume n = a1*a2*ak;
        // result = min((dp(a1)+1)  +(a2*ak -1), (dp(a2)+1) +  (a1*a3 -1).., ak, ...);
        // result = min(dp(ai) + a2*...ak));
        //        = min(dp(a_i) + n / a_i)
        if (n == 1) {
            return 0;
        }
        vector<int> dp(n + 1, INT_MAX);
        // dp[i] is the minimal steps to get i As;
        dp[1] = 0;
        int base = 1;
        while (base < n) {
            for (int i = 2 * base; i <= n; i += base) {
                dp[i] = min(dp[i], dp[base] + i / base);
            }
            base++;
        }
        return dp[n];
    }
};

int main() {

	Solution s;

	return 0;
}
