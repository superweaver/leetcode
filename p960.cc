#include "common.h"
class Solution {
	public:
		int minDeletionSize(vector<string>& A) {
			//int m = A.size();
			int n = A[0].size();
			int max_len = 1;
			// brute force
			// dp[n] is the length of longest increasing subsequcence for all A[i]s and it ends at index n
			vector<int> dp(n, 1);
			for (int i = 0; i < n; ++i) {
				for (int j = i - 1; j >= 0; --j) {
					// dp[j] + 1 > dp[i] to avoid unnecessary check and update
					if (dp[j] + 1 > dp[i] && helper(A, j, i)) {
						dp[i] = max(dp[i], dp[j] + 1);
						max_len = max(max_len, dp[i]);
					}
				}
			}
			return  n - max_len;
		}
	private:
		bool helper(vector<string>&A, int left, int right) {
			for (size_t i = 0; i < A.size(); ++i) {
				if (A[i][left] > A[i][right]) {
					return false;
				}
			}
			return true;
		}

};

int main() {
	vector<string> A = {"babca","bbazb"};
	A = {"ghi","def","abc"};
	A = {"aaaaabaa"};
	Solution s;
	cout << s.minDeletionSize(A) << endl;
	return 0;
}
