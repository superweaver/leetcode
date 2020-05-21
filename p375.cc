#include "common.h"
class Solution {
public:
	int getMoneyAmount(int n) {
		// dp[i][j] is the min money to cover every number from i to j
		// dp[i][j] = min(k + max(dp[i][k], dp[k,j])), for any i < k < j
		// return dp[1][n];
		vector<vector<int> > dp(n + 1, vector<int>(n + 1, 0));
		for (int i = 2; i <= n; ++i) {
            for (int j = i - 1; j > 0; j--) {
                if (j + 1 == i) {
                    dp[j][i] = j;
                } else {
                    int minV = INT_MAX;
                    for (int k = j + 1; k < i; ++k) {
                        minV = min(minV, k + max(dp[j][k - 1], dp[k + 1][i]));
                    }
                    dp[j][i] = minV;
                }
            }
        }
		return dp[1][n];
	}
};

int main() {

	Solution s;

	return 0;
}
