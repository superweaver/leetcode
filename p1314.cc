#include "common.h"
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
		int m = mat.size();
		int n = mat[0].size();
		vector<vector<int>> prefix_sum(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				prefix_sum[i+1][j+1] = prefix_sum[i+1][j] + prefix_sum[i][j+1] - prefix_sum[i][j] + mat[i][j];
			}
        }
		int mp = m;
		int np = n;
		//int mp = m + K;
		//int np = n + K;
        vector<vector<int>> result(mp, vector<int>(np, 0));
		for (int i = 0; i < mp; ++i) {
			for (int j = 0; j < np; ++j) {
				int top = max(0, i - K);
				int bottom = min(i + K, m - 1);
				int left = max(0, j - K);
				int right = min(j + K, n - 1);
				right++;
				bottom++;
                result[i][j] = prefix_sum[bottom][right] + prefix_sum[top][left] -
                               prefix_sum[top][right] - prefix_sum[bottom][left];
            }
		}
		return result;
    }
};

int main() {
    vector<vector<int>> mat = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    int K = 1;

	K = 2;
    Solution s;
	auto r = s.matrixBlockSum(mat, K);
	for (auto&v: r) {
		displayvector(v); 
	}

	return 0;
}
