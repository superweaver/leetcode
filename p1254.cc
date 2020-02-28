#include "common.h"
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
		// 0 island 0, chaneg it to -1 to mark it as visited;
		// 1 is water
		int result = 0;
		int m = grid.size();
		int n = grid[0].size();
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (!grid[i][j]) {
					result += bfs(grid, i, j, m, n);
				}
			}
		}
        for (int i = 0; i < m; ++i) {
			auto&v = grid[i];
            for (int j = 0; j < n; ++j) {
				if (v[j] < 0) {
					v[j] = 0;
				}
            }
        }
        return result;
    }
private:
    const vector<int> dirs{ 0, 1, 0, -1, 0 };
    int bfs (vector<vector<int>>& grid, int r, int c, int m, int n) {
		bool reachboundary = false;
		queue<pair<int, int>> q;
		q.push({r, c});
		grid[r][c] = -1;
		while(!q.empty()) {
			auto current = q.front();
			q.pop();
			for (int i = 0; i < 4; ++i) {
				r = current.first + dirs[i];
				c = current.second + dirs[i + 1];
				if (r < 0 || r >= m || c < 0 || c >= n) {
					reachboundary = true;
					continue;
				}
				if (!grid[r][c]) {
                    grid[r][c] = -1;
                    q.push({ r, c });
                } else {
                    continue;
                }
            }
		}
		return (int)(!reachboundary);
	}
};

int main() {
    vector<vector<int>> grid = { { 1, 1, 1, 1, 1, 1, 1, 0 },
                                 { 1, 0, 0, 0, 0, 1, 1, 0 },
                                 { 1, 0, 1, 0, 1, 1, 1, 0 },
                                 { 1, 0, 0, 0, 0, 1, 0, 1 },
                                 { 1, 1, 1, 1, 1, 1, 1, 0 } };

    grid = { { 1, 1, 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0, 0, 1 }, { 1, 0, 1, 1, 1, 0, 1 },
             { 1, 0, 1, 0, 1, 0, 1 }, { 1, 0, 1, 1, 1, 0, 1 }, { 1, 0, 0, 0, 0, 0, 1 },
             { 1, 1, 1, 1, 1, 1, 1 } };

    Solution s;
	cout << s.closedIsland(grid) << endl;
	return 0;
}
