#include "common.h"
class Solution {
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        // stupid brutal dfs
        int m = grid.size();
        int n = grid[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    result = max(result, dfs(grid, m, n, i, j));
                }
            }
        }
        return result;
    }
private:
  const vector<int> dirs{0, 1, 0, -1, 0};
  int dfs(vector<vector<int>> &grid, int m, int n, int r, int c) {
      if (grid[r][c] == 0) {
          return 0;
      }
      int result = grid[r][c];
      int t = 0;
      for (int d = 0; d < 4; ++d) {
          int i = r + dirs[d];
          int j = c + dirs[d + 1];
          if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0) {
              continue;
          }
          grid[r][c] = 0;
          t = max(t, dfs(grid, m, n, i, j));
          grid[r][c] = result;
      }
      return result += t;
  }
};

int main() {

	Solution s;

	return 0;
}
