#include "common.h"

class Solution {
	// https://www.youtube.com/watch?v=MjOIR61txFc
	// https://www.cnblogs.com/grandyang/p/11108205.html
public:
	int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
		//dp[k][i][j] the # of profitable schemes with j people to gain at least i profit by at most finishing first k crimes
		// assume we have get dp[k-1][i][j], we can choose not to conduct kth crime, this is a part of dp[k][i][j]
		// if we decide to conduct kth crime, we need enough people
		// trick ! profit can't be negative
		// base case: dp[0][0][0] = 1
		const int Mod = 1000000007;
		int K = group.size();
		vector<vector<vector<int>>> dp(K + 1, vector<vector<int>>(P + 1, vector<int>(G + 1, 0)));
		dp[0][0][0] = 1;
		for (int k = 1; k <= K; ++k) {
			const int g = group[k - 1];
			const int p = profit[k - 1];
			for (int i = 0; i <= P; ++i) {
				for (int j = 0; j <= G; ++j) {
					dp[k][i][j] = (dp[k - 1][i][j] + (j < g ? 0 : (dp[k - 1][max(0, i - p)][j - g]))) % Mod;
				}
			}
		}
		return accumulate(dp[K][P].begin(), dp[K][P].end(), 0LL) % Mod;
	}
};

int main() {

	Solution s;

	return 0;
}
