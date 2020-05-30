#include "common.h"
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
        // dp[r][i][j] means upto row r, #1 robot locates at i, #2 robot locates at j, the max
        // cherry we can get dp[0][0][n-1] = grid[0][0] + grid[0][n-1];
        //
        // in next row, there are more states
        int result = dp[0][n - 1] = grid[0][0] + grid[0][n - 1];
        for (int r = 1; r < m; ++r) {
            auto next = dp;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dp[i][j] >= 0) {
//                        cout << "r = " << r << ", (" << i << ", " << j << ")" << endl;
                        for (int ii = -1; ii <= 1; ++ii) {
                            for (int jj = -1; jj <= 1; ++jj) {
                                int ni = i + ii;
                                int nj = j + jj;
                                if (ni < 0 || nj < 0 || ni >= n || nj >= n) {
                                    continue;
                                }
                                int temp = dp[i][j] + grid[r][ni];
                                if (nj != ni) {
                                    temp += grid[r][nj];
                                }
                                next[ni][nj] = max(next[ni][nj], temp);
                            }
                        }
                    }
                }
            }
            next.swap(dp);
        }
        for (auto &v : dp) {
            result = max(result, *max_element(v.begin(), v.end()));
        }
        return result;
    }
};

int main() {
    vector<vector<int>> grid = {{3,1,1},{2,5,1},{1,5,5},{2,1,1}}; // 24
    grid = {{1,0,0,0,0,0,1},{2,0,0,0,0,3,0},{2,0,9,0,0,0,0},{0,3,0,5,4,0,0},{1,0,2,3,0,0,6}}; // 28
    grid = {{1,0,0,3},{0,0,0,3},{0,0,3,3},{9,0,3,3}}; // 22
    grid = {{1,1},{1,1}}; // 4

    Solution s;
    cout << s.cherryPickup(grid) << endl;

    return 0;
}
