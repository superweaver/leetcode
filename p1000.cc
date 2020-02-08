#include "common.h"
class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
		// dp
		int n = stones.size();
		if ((n - 1) % (K - 1) != 0) {
			return -1;
		}
		vector<int> prefix_sum(n + 1, 0);
		for (int i = 0; i < n; ++i) {
			prefix_sum[i + 1] = prefix_sum[i] + stones[i];
		}
		// int rangesum = prefix_sum[end + 1] - prefix_sum[start];
		const int Big = 1000000000;
		
		// dp[i][j][k] means the min merge cost from stones[i ..j] and ending with k stones left
		// note : k = (len - 1) % (K - 1) + 1 !!!!
		// dp[i][i][1] = 0; // not cost for merge
		// dp[i][j][k] = min(dp[i][m][lk] + dp[m+1][j][rk]), m = i + 1,...,j - 1
		// if (k == K) dp[i][j][1] = dp[i][j][k] + prefix_sum[j + 1] - prefix_sum[i]; // do actual merge
		// return dp[i][j][1]
		//
		// since k is completely determined by the lenth of [i..j] there is no need to have such variable
		vector<vector<int>> dp(n, vector<int>(n, Big));
		for (int i = 0; i < n; ++i) {
			dp[i][i] = 0; // no merge cost
		}
		// sub problem have no overlaps.
		for (int len = 2; len <= n; ++len) { // length, from sub problem to whole problem
			for (int i = 0; i - 1 + len < n; ++i) { // start
				int j = len + i - 1; // end // j < n
				int k = (len - 1) % (K-1)  + 1;  // how many piles in the end
				for (int m = i; m < j; m += K - 1) { // m += K - 1
					dp[i][j] = min(dp[i][j], dp[i][m] + dp[m+1][j]);
				}
				if (k == 1) {
					// do the merge !!!1
					// key , the delta is determined by i, j
					dp[i][j] += prefix_sum[j + 1] - prefix_sum[i];
				}
			}
		}
		return dp[0][n-1];
	}
};
int main() {

	vector<int> A = {3,5,1,2,6}; // 25;
	int K = 3;
//	A = {3, 2, 4, 1};
	//K = 2;
	Solution s;
	cout << s.mergeStones(A, K) << endl;

	return 0;
}
