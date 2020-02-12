#include "common.h"
class Solution
{
  public:
	int maxUncrossedLines(vector<int> &A, vector<int> &B)
	{
		// https://yuuuuuy.top/2019/10/29/LeetCode-1035-Uncrossed-Lines/
		// dp
		// dp[i][j] means how many Uncrossed Lines we can get using first i
		// elements of A and first j elements of B
		// base case : dp[0][x] = 0, dp[x][0] = 0
		// if A[i] == B[j], then dp[i][j] = 1 + dp[i-1][j-1]
		// if A[i] != B[j], then dp[i][j] = max(dp[i-1][j], dp[i][j-1])
		int m = A.size();
		int n = B.size();
		/*
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		int result = 0;
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (A[i - 1] == B[j - 1]) { // be careful here
					dp[i][j] = 1 + dp[i - 1][j - 1];
					result = max(result, dp[i][j]);
				} else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
					// no need to update result here
				}
			}
		}
		return result;
		*/
		vector<int> pre(n + 1, 0);
		vector<int> dp(n + 1, 0);
		int result = 0;
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (A[i - 1] == B[j - 1]) { // be careful here
					dp[j] = 1 + pre[j - 1];
					result = max(result, dp[j]);
				} else {
					dp[j] = max(pre[j], dp[j - 1]);
					// no need to update result here
				}
			}
			swap(dp, pre);
		}
		return result;
	}
};

int main()
{
	vector<int> A = {2, 5, 1, 2, 5}, B = {10, 5, 2, 1, 5, 2};
	Solution s;
	cout << s.maxUncrossedLines(A, B) << endl;
	return 0;
}
