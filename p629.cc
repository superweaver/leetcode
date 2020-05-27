#include "common.h"
using namespace std;
class Solution {
public:
//https://www.cnblogs.com/grandyang/p/7111385.html
//https://blog.csdn.net/magicbean2/article/details/79006767

	int kInversePairs(int n, int k) {
	// dp[i][j] is the number of ways to allow number 1...i to have exactly j inverse pairs
	// then consider dp[i+1][j]
	// assume [a1, a2, ..., ai]
	// then if we put i+1 in the end of [a1, a2, ..., ai], it won't increase number of inverse pairs
	// if we put i+1 before ai, [a1, a2, ..., i+1, ai], it will add one inverse pairs;
	// similarly, to form j inverse pairs, [a1, a2, ... , ai] need to put (k-m) inverse pairs, and then put i+1
	// m distance away from the end of ai (i + 1 will form the m invese pairs)
	// dp[i+1][j] = dp[i][j] + dp[i][j-1] + ....+dp[i][j-i]; // dp[i][j-i] corresponds to put i+1 in the beginning
	// (1) dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + ...+ dp[i-1][j-i+1];
	// (2) dp[i][j+1] = dp[i-1][j+1] + dp[i-1][j] ... +dp[i-1][j-i];
	// (2) - (1)
	// dp[i][j+1] = dp[i][j] + dp[i-1][j+1] - dp[i-1][j-i+1];
	// dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-i]
	// can optimize space
	// base case dp[i][0] = 1
		const int M = 1e9 + 7;
		vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
		dp[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			dp[i][0] = 1;
			for (int j = 1; j <= k; ++j) {
				dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % M;
				if (j >= i) {
					dp[i][j] -= dp[i - 1][j - i];
					dp[i][j] = (dp[i][j] + M) % M;
				}
			}
		}
		return dp[n][k];
	}
};

int main() {

	Solution s;

	return 0;
}
