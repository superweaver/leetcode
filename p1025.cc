#include "common.h"
class Solution {
public:
    bool divisorGame(int N) {
		return !(N&1);
		// why it works
		// if N % 2 == 0
		// Alice choose 1
		// then N-1 is odd, which is for bob
		// if (N-1) = 1, bob lose
		// else the factor x for N-1 must be also odd, otherwise N -1 is even
		// then (N-1) - x must be even
		// back to Alice
	}
	// my solution
    bool divisorGame_hai(int N) {
		// n^2
        vector<int> dp(N+1, -1);
		return (bool)helper(N, dp);
    }
private:
	int helper(int n, vector<int>& dp) {
		if (n <= 1) {
			return dp[n] = 0;
		}
		if (dp[n] >= 0) {
			return dp[n];
		}
		for (int x = 1; x < n; ++x) {
			if (n % x == 0) {
				if (helper(n-x, dp)) {
					continue;
				} else {
					return dp[n] = 1;
				}
			}
		}
		return dp[n] = 0;
	}
};

int main() {

	Solution s;
	int n = 2;
	n = 3;
	cout << s.divisorGame(n) << endl;

	return 0;
}
