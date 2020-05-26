#include "common.h"
class Solution {
public:
	//https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/
	// dp
	// dp[i][j] is the length of longest palindromic subsequence of s[i...j] (inclusively)
	// base case dp[i][i] = 1
	// base case dp[i][i+1] == 2 if s[i] == s[i+1]
	// if s[i] == s[j], then dp[i][j] = dp[i+1][j-1] + 2, if i+1 <= j - 1
	// if s[i] != s[j], then dp[i][j] = max(dp[i+1][j], dp[i][j-1])
	// return s[0][n-1]
	int longestPalindromeSubseq(string s) {
		int n = s.size();
		if (n <= 1) {
			return n;
		}
		vector<vector<int> > dp(n, vector<int>(n, 0));
		// len == 1
		for (int i = 0; i < n; ++i) {
			dp[i][i] = 1;
		}
		for (int len = 2; len <= n; ++len) {
			for (int i = 0; i + len - 1 < n; ++i) { // i is the start index of segment
				int j = i + len - 1; // j is the end index of segment
				if (s[i] == s[j]) {
					if (len == 2) {
						// j == i + 1, base case
						dp[i][j] = 2;
					}
					else { // len > 2
						dp[i][j] = dp[i + 1][j - 1] + 2;
					}
				}
				else {
					// both dp[i+1][j] and dp[i][j-1] have been obtained in len - 1
					dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
				}

			}
		}
		return dp[0][n - 1];
	}
};

int main() {

	Solution s;

	return 0;
}
