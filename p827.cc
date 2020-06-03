#include "common.h"
class Solution {
  public:
      // acutally, during bfs, we can record candidates of 0
    int largestIsland(vector<vector<int>> &grid) {
        int n = grid.size();
        int len = n * n;
        // vector<int> parents(len);
        // vector<int> size(len, 1);
        // for (int i = 0; i < len; ++i) {
        //	parents[i] = i;
        //}
        int gid = 1;
        vector<int> size(1, 0);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            auto &v = grid[i];
            for (int j = 0; j < n; ++j) {
                if (v[j] == 1) {
                    int ones = bfs(grid, i, j, n, gid++);
                    size.push_back(ones);
                    result = max(result, ones);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            auto &v = grid[i];
            for (int j = 0; j < n; ++j) {
                if (v[j] == 0) {
                    int r = 0;
                    unordered_set<int> neighbors;
                    for (int k = 0; k < 4; ++k) {
                        int row = i + operations[k][0];
                        int col = j + operations[k][1];
                        if (row < 0 || col < 0 || row >= n || col >= n || grid[row][col] == 0) {
                            continue;
                        }
                        // size[0] = 0;
                        neighbors.insert(grid[row][col] >> 8);
                    }
                    for (auto x : neighbors) {
                        r += size[x];
                    }
                    r++;
                    result = max(result, r);
                }
            }
        }
        return result;
    }

  private:
    const vector<vector<int>> operations = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int bfs(vector<vector<int>> &grid, int r, int c, int n, int gid) {
        queue<pair<int, int>> q;
        q.push({r, c});
        int count = 0;
        int mask = gid << 8;
        grid[r][c] += mask;
        count++;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto current = q.front();
                q.pop();
                for (int i = 0; i < 4; ++i) {
                    int row = current.first + operations[i][0];
                    int col = current.second + operations[i][1];
                    if (row >= 0 && col >= 0 && row < n && col < n && grid[row][col] == 1) {
                        q.push({row, col});
                        grid[row][col] += mask;
                        count++;
                    }
                }
            }
        }
        return count;
    }
};

int main() {

	Solution s;

	return 0;
}
