#include "common.h"
class Solution {
public:
	int matrixScore(vector<vector<int>>& A) {
		int m = A.size();
		int n = A[0].size();
		for (int i = 0; i < m; ++i) {
			if (A[i][0] == 0) {
				auto &v = A[i];
				for (auto&k : v) {
					k = 1 - k;
				}
			}
		}
		vector<int> count;
		for (int j = n - 1; j >= 0; --j) {
			int ones = 0;
			for (int i = 0; i < m; ++i) {
				ones += A[i][j];
			}
			ones = ones > (m - ones) ? ones : m - ones;
			count.push_back(ones);
		}
		int r = 0;
		for (int i = 0; i < n; ++i) {
			r += count[i] * (1 << i);
		}
		return r;
	}
};

int main() {

	Solution s;

	return 0;
}
