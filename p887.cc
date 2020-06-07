#include "common.h"
class Solution {
public:
	int superEggDrop(int K, int N) {
		// dp[i][j] is the max floors we can measure with i moves and j eggs
        //
		// dp[i][j] means the ith moves && using the jth egg to measure dp[i-1][j-1] + 1 floor
		// if egg breaks, then in [1 to dp[i-1][j-1]] egg won't break;
		// if egg doesn't break, then it can be reused. we can find dp[i-1][j] more floors (above the previous testing floor)
		// so dp[i][j] = dp[i-1][j-1] + d[i-1][j] + 1 // 1 means the testing floor
		// when dp[i][K] >= N, return i
		// space can be optimized
		vector<int> dp(K + 1, 0);
		int i = 0;
		while (dp[K] < N) {
			++i;
			for (int j = K; j > 0; --j){
				dp[j] = dp[j - 1] + dp[j] + 1;
			}
		}
		return i;
	}
	int superEggDrop1(int K, int N) {
		//https://www.cnblogs.com/grandyang/p/11048142.html
		// dp[i][j] is the minimum moves to measure j floors with i eggs
		// for any k, 1 <= k <= j, try to drop an egg
		// if it breaks, we need to use the rest of i - 1 eggs to measure k - 1 floors (1 ... k - 1)
		// if it doesn't break, then we can i eggs to measure the above j - k floors
		// dp[i][j] = min(dp[i][j], max(dp[i-1][k-1], dp[i][j-k]) + 1 ) for any 1 <= k <= j
        //
		// note: for dp[i-1][k-1], this increases as k increases while dp[i][j-k] decreases as k increases
		// method 1, use binary search to find the first k in [1, j] so that dp[i-1][k-1] >= dp[i][j-k]
		// note at this moment, max(dp[i-1][k-1], dp[i][j-k]) get its min value
        //
		// method 2, dp[i][j-k] will increase with j;
		// use s to represent the first k so that dp[i-1][k-1] >= dp[i][j-k]
		// when j increase, we can use move from previous finding s to find new s
		vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
		// K == 1
		for (int j = 1; j <= N; ++j) {
			dp[1][j] = j;
		}
		for (int i = 2; i <= K; ++i) {
			int s = 1;
			for (int j = 1; j <= N; ++j) {
				dp[i][j] = j;
				// find the first k so that dp[i-1][k-1] >= dp[i][j-k]
				while (s < j && dp[i - 1][s - 1] < dp[i][j - s]) {
					++s;
				}
				dp[i][j] = min(dp[i][j], max(dp[i - 1][s - 1], dp[i][j - s]) + 1);
			}
		}
		return dp[K][N];
	}
};

int main() {

	Solution s;

	return 0;
}
