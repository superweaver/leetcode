#include "common.h"
class Solution {
public:
	int longestArithSeqLength(vector<int>& A) {
		int n = A.size();
		vector<vector<int>> dp(n, vector<int>(n, 0));
		// dp[i][j] is the length of Arithmetic Sequence whose last two elements are A[i] and A[j]
		vector<int> v2i(10001, -1);// record the last index of v
		int result = 2;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				dp[i][j] = 2; // at least 2;
				int pre = 2 * A[i] - A[j];
				if (pre < 0 || pre > 10000 || v2i[pre] < 0) {
					continue;
				}
				int index = v2i[pre];
				dp[i][j] = dp[index][i] + 1;
				result = max(dp[i][j], result);
			}
			v2i[A[i]] = i; // update or overwirte;
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
