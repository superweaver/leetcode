#include "common.h"
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
		int m = mat.size();
		int n = mat[0].size();
		for (int i = m -1; i >= 0; --i) { // j = 0;
			vector<int> temp;
			int r = i;
			int c = 0;
			while(r < m && c < n) {
				temp.push_back(mat[r][c]);
				r++;
				c++;
			}
			sort(temp.begin(), temp.end());
			r = i;
			c = 0;
			int index = 0;
			while(r < m && c < n) {
				mat[r++][c++] = temp[index++];
			}
		}
		for (int j = 1; j < n; ++j) {
            vector<int> temp;
            int r = 0;
            int c = j;
            while (r < m && c < n) {
                temp.push_back(mat[r][c]);
                r++;
                c++;
            }
            sort(temp.begin(), temp.end());
            r = 0;
            c = j;
            int index = 0;
            while (r < m && c < n) {
                mat[r++][c++] = temp[index++];
            }
        }
		return mat;
    }
};

int main() {
    vector<vector<int>> input = { { 3, 3, 1, 1 }, { 2, 2, 1, 2 }, { 1, 1, 1, 2 } };
    Solution s;
	s.diagonalSort(input);
	for(auto& v : input) {
		displayvector(v);
	}
	return 0;
}
