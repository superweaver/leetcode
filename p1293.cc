#include "common.h"
class Solution {
  public:
    /*
     Given a m * n grid, where each cell is either 0 (empty) or 1 (obstacle). In one step, you can move up, down, left or right from and to an empty cell.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m-1, n-1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.
     */
    int shortestPath(vector<vector<int>> &grid, int k) {
        // https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/discuss/490617/C%2B%2B-beats-100!-0ms!-With-explanation-and-production-ready-coding-style
        // 1. As it was mentioned here there is an optimization using Manhattan distance which improves the overall running time dramatically.
        // 2. Also, we could do some pruning based on the Manhattan distance calling the recursive function only if it improves the result.
        //3. Another little trick is to go down and right and only then check up and left.
        if (grid.empty() || grid[0].empty()) {
            return -1;
        }
        m = grid.size();
        n = grid[0].size();
        minSteps = INT_MAX;
        bfs(0, -1, -1, 0, 0, k, grid);
        return minSteps == INT_MAX ? -1 : minSteps;
    }

  private:
    int minSteps;
    int m;
    int n;
    unordered_set<int> memo;
    //const vector<int> dirs = {0, 1, 0, -1, 0};
    const vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    // 1 <= m, n <= 40
    // key = (k << 16) + (m << 8) + n;
    inline int tokey(int r, int c, int k) { return (k << 16) + (r << 8) + c; }
    int getdistance(int r, int c) { return m - 1 - r + n - 1 - c; }
    bool isValid(int r, int c) { return r >= 0 && r < m && c >= 0 && c < n; }

    void bfs(int steps, int pre_r, int pre_c, int r, int c, int k, vector<vector<int>> &grid) {

        // current is 0 !!!
        // shortcut (1)
        if (k >= m + n - 3 - r - c) {
            // k is big enough
            // we can get a manhaton minimum distance
            minSteps = min(minSteps, steps + (m + n - 2 - r - c));
            return;
        }
        // get destination
        if ((r == m - 1) && (c == n - 1)) {
            minSteps = min(minSteps, steps);
            return;
        }

        int key = tokey(r, c, k);
        if (memo.count(key)) {
            return;
        } else {
            memo.insert(key);
        }

        int curr_dist = getdistance(r, c);
        for (auto &dir : dirs) {
            int next_r = r + dir[0];
            int next_c = c + dir[1];
            if (!(next_r == pre_r && next_c == pre_c) && isValid(next_r, next_c)) {
                int next_dist = getdistance(next_r, next_c);
                if (grid[next_r][next_c] == 0) {
                    // must check
                    bfs(steps + 1, r, c, next_r, next_c, k, grid);
                } else if (next_dist < curr_dist && k >= 1) {
                    bfs(steps + 1, r, c, next_r, next_c, k - 1, grid);
                }
            }
        }
    }
};

int main() {
    vector<vector<int>> grid = {{0,0,0}, {1,1,0}, {0,0,0}, {0,1,1}, {0,0,0}};

    int k = 1;

    grid = {{0,1,1}, {1,1,1}, {1,0,0}}, k = 1;

    Solution s;
    cout << s.shortestPath(grid, k) << endl;

    return 0;
}
