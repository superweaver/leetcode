#include "common.h"
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
		int m = matrix.size();
		int n = matrix[0].size();
		vector<int> mr(m, INT_MAX); // min value of m rows
		vector<int> mc(n, INT_MIN); // max values of n column
		for (int i = 0; i < m; ++i) {
			auto v = matrix[i];
			for (int j = 0; j < n; ++j) {
				mr[i] = min(mr[i], v[j]);
				mc[j] = max(mc[j], v[j]);
			}
		}
		vector<int> result;
        for (int i = 0; i < m; ++i) {
            auto v = matrix[i];
			for (int j = 0; j < n; ++j) {
				if (v[j] == mr[i] && v[j] == mc[j]) {
					result.push_back(v[j]);
				}
			}
        }
		return result;
    }
};

int main() {
	vector<vector<int>> matrix = {{3,7,8},{9,11,13},{15,16,17}};
	Solution s;
	displayvector(s.luckyNumbers(matrix));
	return 0;
}
