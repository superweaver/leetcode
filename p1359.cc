#include "common.h"
class Solution {
public:
    int countOrders(int n) {
        // dp
        // assume we know dp[i]
        // for any of it  there are total of t = 1 + 2*i slots
        // pick one for p[i+1], assume it is k (k = 0, ... t-1)
        // then you can pick t - k slots for d[i + 1]
        // so the total = (1 + t) * t / 2
        // dp[0] = 1; // one way;
        // dp[i+1] = dp[i] * ways for i+1th order = dp[i-1] * (2 + 2 * i ) * (1 + 2 * i) / 2;
        // dp[i + 1] = dp[i] * (1+i) * (2*i + 1);
        long long dp = 1;
		int Mod = 1000000007;
        for (int i = 0; i < n; ++i) {
            dp *= (1 + i) * (2 * i + 1);
			dp %= Mod;
        }
		return dp;
    }
};

int main() {

	Solution s;
	for (int i = 0; i < 10; ++i) {
		cout << i << " : " << s.countOrders(i) << endl;
	}
	return 0;
}
