#include "common.h"
class Solution {
	//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-741-cherry-pickup/,
public:
	int cherryPickup(vector<vector<int>>&grid) {
		// assume there is a round path from (0, 0) to (n-1, n-1) to get max cherries
		// the it is equal to two people start from (n-1, n-1) and pick cherries independently
		// meet at (0, 0), at same grid, cherry can only be picked by one people
		//constraint: x1 + y1 = x2 + y2; (steps are same);
		int n = grid.size();
		vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
		return max(pick(dp, grid, n - 1, n - 1, n - 1), 0);
	}
private:
	int pick(vector<vector<vector<int>>> &dp, vector<vector<int>>&grid, int r1, int c1, int r2) {
		int n = grid.size();
		int c2 = r1 + c1 - r2;
		if (r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0) {
			return -1; // no available
		}
		if (r1 >= n || c1 >= n || r2 >= n || c2 >= n) {
			return -1;
		}
		if (grid[r1][c1] < 0 || grid[r2][c2] < 0) { return dp[r1][c1][r2] = -1; } // not available
		if (r1 == 0 && c1 == 0 && r2 == 0) {
			return grid[r1][c1]; // base;
		}
		if (dp[r1][c1][r2] != INT_MIN) { // calculated
			return dp[r1][c1][r2];
		}
		// step from left and top
		int r = max(max(pick(dp, grid, r1-1, c1, r2-1), pick(dp, grid, r1, c1-1, r2)), max(pick(dp, grid, r1-1, c1, r2), pick(dp, grid, r1, c1-1, r2-1)));
		if (r < 0) {
			return dp[r1][c1][r2] = -1; // no solution
		}
		r += grid[r1][c1];
		if (r1 != r2) {
			r += grid[r2][c2];
        } // else { r+=0; has been picked}
        return dp[r1][c1][r2] = r;
	}
};

int main() {

	Solution s;

	return 0;
}
