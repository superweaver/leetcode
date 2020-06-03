#include "common.h"
// https://leetcode.com/problems/bricks-falling-when-hit/discuss/141229/JAVA-Simple-DFS-16ms-reversely-add-bricks-back
// union-find : nice
// https://leetcode.com/problems/bricks-falling-when-hit/discuss/195781/Union-find-Logical-Thinking
//
class Solution {
  public:
    vector<int> hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits) {
        int m = grid.size();
        int n = grid[0].size();
        int k = hits.size();
        vector<int> res(k);
        unordered_set<int> noDrop;
        for (int i = 0; i < k; ++i) {
            grid[hits[i][0]][hits[i][1]] -= 1;
        }
        for (int i = 0; i < n; ++i) {
            if (grid[0][i] == 1) {
                check(grid, 0, i, noDrop);
            }
        }

        for (int i = k - 1; i >= 0; --i) {
            int oldSize = noDrop.size(), x = hits[i][0], y = hits[i][1];
            if (++grid[x][y] != 1) {
                continue;
            }

            if ((x - 1 >= 0 && noDrop.count((x - 1) * n + y)) ||
                (x + 1 < m && noDrop.count((x + 1) * n + y)) ||
                (y - 1 >= 0 && noDrop.count(x * n + y - 1)) ||
                (y + 1 < n && noDrop.count(x * n + y + 1)) || x == 0) {
                check(grid, x, y, noDrop);
                res[i] = noDrop.size() - oldSize - 1;
            }
        }
        return res;
    }
    void check(vector<vector<int>> &grid, int i, int j, unordered_set<int> &noDrop) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 1 || noDrop.count(i * n + j))
            return;
        noDrop.insert(i * n + j);
        check(grid, i - 1, j, noDrop);
        check(grid, i + 1, j, noDrop);
        check(grid, i, j - 1, noDrop);
        check(grid, i, j + 1, noDrop);
    }
};
// Author: Huahua
// Running time: 1261 ms
// // similar to this https://leetcode.com/problems/bricks-falling-when-hit/discuss/120057/C%2B%2B-DFS-(similar-to-LC749)
//
class Solution_hua {
  public:
    vector<int> hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits) {
        dirs_ = {0, -1, 0, 1, 0};
        m_ = grid.size();
        n_ = grid[0].size();
        g_.swap(grid); // back up
        seq_ = 1;      // a unique id to fill into grid and mark certain grid has been visited

        vector<int> ans;
        for (int i = 0; i < hits.size(); ++i) {
            ans.push_back(hit(hits[i][1], hits[i][0]));
        }
        return ans;
    }

  private:
    vector<vector<int>> g_;
    vector<int> dirs_;
    int seq_;
    int m_;
    int n_;

    // hit x, y and return the number of bricks fallen.
    int hit(int x, int y) {
        if (x < 0 || x >= n_ || y < 0 || y >= m_) {
            return 0;
        }
        g_[y][x] = 0; // mark it as 0 (hit)
        int ans = 0;
        for (int i = 0; i < 4; ++i) {
            ++seq_;
            int count = 0;
            if (!fall(x + dirs_[i], y + dirs_[i + 1], false, count)) {
                continue;
            }
            ++seq_;
            ans += count;
            fall(x + dirs_[i], y + dirs_[i + 1], true, count);
        }
        return ans;
    }

    // Check whether the CC contains (x, y) will fall or not.
    // Set all nodes in this CC as seq_ or 0 if clear.
    // count: the # of nodes in this CC.
    bool fall(int x, int y, bool clear, int &count) {
        if (x < 0 || x >= n_ || y < 0 || y >= m_) {
            return true;
        }
        if (g_[y][x] == seq_ || g_[y][x] == 0) {
            return true;
        }
        if (y == 0) { // first row
            return false;
        }
        g_[y][x] = clear ? 0 : seq_;
        ++count;
        for (int i = 0; i < 4; ++i) {
            if (!fall(x + dirs_[i], y + dirs_[i + 1], clear, count)) {
                return false;
            }
        }
        return true;
    }
};

int main() {

    Solution s;

    return 0;
}
