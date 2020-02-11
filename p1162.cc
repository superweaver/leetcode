#include "common.h"
class Solution {
	public:
		int maxDistance(vector<vector<int>>& grid) {
			int n = grid.size();
			int result = 0;	
			queue<pair<int, int>> q;
			for (int i = 0; i < n; ++i) {
				for(int j = 0; j < n; ++j) {
					if (grid[i][j]) {
						q.push({i, j});
					}
				}
			}
			if (q.empty() || (int)q.size() == n * n) {
				return -1;
			}
			vector<int> dirs = {0, -1, 0, 1, 0};
			while (!q.empty()) {
				size_t size = q.size();
				while(size--) {
					auto p = q.front();
					q.pop();
					for (int i =0;  i < 4; ++i) {
						int r = p.first + dirs[i];
						int c = p.second + dirs[i+1];
						if (r < 0 || c < 0 || r >= n || c >= n) {
							continue;
						}
						if (grid[r][c] == 0) {
							grid[r][c] = -1;
							q.push({r, c});
						}
					}
				}
				if (!q.empty()) {
					result++;
				}
			}
			return result;
		}
};

int main() {
	vector<vector<int>> grid = {{1,0,1},{0,0,0},{1,0,1}};
	Solution s;
	cout << s.maxDistance(grid) << endl;
    return 0;
}
