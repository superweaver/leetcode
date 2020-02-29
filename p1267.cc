#include "common.h"
class Solution {
public:
    int countServers(vector<vector<int>>& grid)
    {
        int m = grid.size();
		int n = grid[0].size();
		vector<int> rowsum(m, 0);
		vector<int> columnsum(n, 0);
		int total = 0;
		for (int i = 0; i < m; ++i) {
			auto &v = grid[i];
			for (int j = 0; j < n; ++j) {
				rowsum[i] += v[j];
				columnsum[j] += v[j];
                total += v[j];
            }
		}
		int result = total;
		vector<int> one_r;
		for (int i = 0; i < m; ++i) {
			if (rowsum[i] == 1) {
				one_r.push_back(i);
			}
		}
		vector<int> one_c;
		for (int j = 0; j < n; ++j) {
			if(columnsum[j] == 1) {
                one_c.push_back(j);
            }
		}
		for (auto i : one_r) {
			for (auto j : one_c) {
				if (grid[i][j]) {
					result--;
				}
			}
		}
		return result;
    }

    int countServers2(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		vector<int> rowsum(m, 0);
		vector<int> columnsum(n, 0);
		int total = 0;
		for (int i = 0; i < m; ++i) {
			auto &v = grid[i];
			for (int j = 0; j < n; ++j) {
				rowsum[i] += v[j];
				columnsum[j] += v[j];
                total += v[j];
            }
		}
		int result = total;
		for (int i = 0; i < m; ++i) {
            if (rowsum[i] != 1) {
                continue;
			}
			auto&v = grid[i];
			for (int j = 0; j < n; ++j) {
				// rowsum[i] == 1
				// v[j] == 1 is mandatory
				if (v[j] && columnsum[j] == 1) {
					result--;
				}
			}
		}
		return result;	
    }
};

int main() {

    vector<vector<int>> grid = { { 1, 0 }, { 0, 1 } };
    grid = { { 1, 0 }, { 1, 1 } };
	grid = {{1,1,0,0},{0,0,1,0},{0,0,1,0},{0,0,0,1}};
    Solution s;
	cout << s.countServers(grid) << endl;
	return 0;
}
