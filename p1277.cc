#include "common.h"
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix)
    {
        // my solution
        int m = matrix.size();
        int n = matrix[0].size();
		int total = 0;
		for (int i = 0; i < m; ++i) {
			total += matrix[i][0];
		}
        auto& v = matrix[0];
        for (int j = 1; j < n; ++j) {
            total += v[j];
        }
		// matrix[i][j] is the length of max square with bottom right at (i, j)
        for (int i = 1; i < m; ++i) {
			auto&pre = matrix[i-1];
			auto&current = matrix[i];
            for (int j = 1; j < n; ++j) {
				if (current[j]) {
					total += (current[j] += min(pre[j-1], min(pre[j], current[j-1])));
				}
				/*
                if (matrix[i][j]) {
					total += (matrix[i][j] = min(matrix[i-1][j-1], min(matrix[i-1][j], matrix[i][j-1])) + 1);
                }
				*/
            }
        }
		return total;
    }

    int countSquares_mine(vector<vector<int>>& matrix) {
		// my solution
		int m = matrix.size();
        int n = matrix[0].size();
		int total = 0;
		for (int i = 0; i < m; ++i) {
			total += matrix[i][0];
			if (matrix[i][0]) {
				// left length of ones, top length of ones, topleft max square length
                matrix[i][0] = (1 << 16) + (1 << 8) + 1;
            }
		}
        auto& v = matrix[0];
        for (int j = 1; j < n; ++j) {
			total += v[j];
            if (v[j]) {
                v[j] = (1 << 16) + (1 << 8) + 1;
            }
        }
        for (int i = 1; i < m ;++i) {
			for (int j = 1; j < n; ++j) {
				if (matrix[i][j]) {
					int left = matrix[i][j-1];
					int top = matrix[i-1][j];
					int leftlen = (left >> 16) + 1;
					int toplen = ((top & 0xFF00) >> 8) + 1;
					int topleft = matrix[i-1][j-1];
                    int topleft_rec_len = topleft & 0xFF;
					int rect_len = min(topleft_rec_len + 1, min(leftlen, toplen));
					total +=  rect_len;
					matrix[i][j] = (leftlen << 16) + (toplen << 8) + rect_len;
                }
			}
		}
		return total;
    }
};

int main() {

    vector<vector<int>> matrix = { { 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 0, 1, 1, 1 } }; // 15
	matrix = { {1,0,1}, {1,1,0}, {1,1,0} }; // 7;

    Solution s;
    cout << s.countSquares(matrix) << endl;
    return 0;
}
