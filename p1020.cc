#include "common.h"
class Solution {
  public:
    int numEnclaves(vector<vector<int>> &A) {
        int m = A.size();
        int n = A[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (A[i][j] == 1) {
                    result += bfs(A, i, j, m, n);
                }
            }
        }
        return result;
    }

  private:
    const vector<int> dirs = {0, 1, 0, -1, 0};
    int bfs(vector<vector<int>> &A, int r, int c, int m, int n) {
        queue<pair<int, int>> q;
        q.push({r, c});
        A[r][c] = -1;
        bool crossboundary = false;
        int count = 0;
        while (!q.empty()) {
            size_t size = q.size();
            count += size;
            while (size--) {
                auto p = q.front();
                q.pop();
                for (int i = 0; i < 4; ++i) {
                    r = p.first + dirs[i];
                    c = p.second + dirs[i + 1];
                    if (r >= 0 && r < m && c >= 0 && c < n) {
                        if (A[r][c] == 1) {
                            A[r][c] = -1;
                            q.push({r, c});
                        }
                    } else {
                        crossboundary = true;
                    }
                }
            }
        }
        return crossboundary ? 0 : count;
    }
};

int main() {

	Solution s;

	return 0;
}
