#include "common.h"

class Solution {
public:

    int numRollsToTarget(int d, int f, int target) {
		if (target < d || target > d * f) {
			return 0;
		}
		// dp[i][j] = sum(dp[i-1][j-k]), k = 1, 2, .. f
        vector<vector<int>> dp(d + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;
		for (int i = 1; i <= d; ++i) {
			for (int j = 1; j <= target; ++j) {
				for (int k = 1; k <= f; ++k) {
                    if (j - k < i - 1 || j - k > (i - 1) * f) {
                        continue;
					}
                    dp[i][j] += dp[i-1][j-k];
					dp[i][j] %= Mod;
				}
			}
		}
		return dp[d][target];
    }
private:
	const int Mod = 1000000007;
};

int main() {

	int d = 1, f = 6, target = 3; // 1
    d = 2, f = 6, target = 7; // 6
	d = 2, f = 5, target = 10;
	d = 1, f = 2, target = 3;
    d = 30, f = 30, target = 500;
    Solution s;
	cout << s.numRollsToTarget(d, f, target) << endl;

	return 0;
}
