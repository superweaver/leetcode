#include "common.h"
class Solution {
public:
	int minimumDeleteSum(string s1, string s2) {
		int m = s1.size();
		int n = s2.size();
        //	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        vector<vector<int>> lcs_sum(m + 1, vector<int>(n + 1, 0));
		// dp[i][j] = max(dp[i-1][j-1] + 1 if s1[i-1] == s2[j-1], dp[i][j-1], dp[i][j-1])
		// trace back for longest common sequence
		// dp[0][0] = 0;
		// directly get sum;
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
			//	dp[i][j] = dp[i-1][j-1] + (s1[i-1] == s2[j-1]);
			//	dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i][j-1]));
				lcs_sum[i][j] = lcs_sum[i - 1][j - 1] + (s1[i - 1] == s2[j - 1])*s1[i-1];
				lcs_sum[i][j] = max(lcs_sum[i][j], max(lcs_sum[i-1][j], lcs_sum[i][j-1]));
			}
		}

		int result = 0;
		for (auto c : s1) {
			result += c;
		}
		for (auto c : s2) {
			result += c;
		}
		return result - 2 * lcs_sum[m][n];
	}
};

int main() {

	Solution s;

	return 0;
}
