#include "common.h"
// https://en.wikipedia.org/wiki/Hamiltonian_path
// count the number or Hamiltonian path
// https://zxi.mytechroad.com/blog/searching/leetcode-980-unique-paths-iii/
class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
       // (1) burtal force dfs 
	   int m = grid.size();
	   int n = grid[0].size();
	   int start_r = -1;   
	   int start_c = -1;
	   int zeros = 0;
	   for (int i = 0; i < m; ++i) {
		   for (int j = 0; j < n; ++j) {
			   if (grid[i][j] == 1) {
				   start_r = i;
				   start_c = j;
			   }
			   zeros += (grid[i][j] == 0);
		   }
	   }
	   zeros += 1; // this is for start point 1 !!!!
	   // example : [1 2 0]
	   return dfs_bf(grid, start_r, start_c, zeros, m, n);
    }
	// (2) dp
	/*
    int uniquePathsIII_dp(vector<vector<int>>& grid) {
		// dp[r][c][state] means the # paths from start point to r, c and ending at state "state"
		// note: m * n <= 20		
		// initial state at start point is s where all bits corresponding to 0s and 2 are set to 1
		// final state at end point should be 0
		int m = grid.size();
		int n = grid[0].size();
		int start_r = -1;   
		int start_c = -1;
		int state = 0;
		vector<int> dirs = {0, 1, 0, -1, 0};
		vector<vector<vector<int>>>	 dp(m, vector<vector<int>>(n, vector<int>((1 << (m * n)) - 1, -1)));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (grid[i][j] == 1) {
					start_r = i;
					start_c = j;
				}
				if (grid[i][j] == 0 || grid[i][j] == 2) {
					state |=  (1 << (i * n + j));
				}
			}
		}
		function<int(int, int, int)> dfs_dp  = [&] (int r, int c, int state) {
			if (dp[r][c][state] != -1) {
				return dp[r][c][state];
			}
			if (grid[r][c] == 2) {
				return (state == 0) ? 1 : 0;
			}
			int paths = 0;
			for (int i = 0; i < 4; ++i) {
				int nr = r + dirs[i];
				int nc = c + dirs[i+1];
				int key = 1 << (nr * n + nc);
				if (nr < 0 || nr >= m || nc < 0 || nc >= n || !(state&key)) {
					continue;
				}
				paths += dfs_dp(nr, nc, state & (~key));
			}
			return dp[r][c][state] = paths;
		};
		return dfs_dp(start_r, start_c, state);
	}
	*/
private:
	int dfs_bf(vector<vector<int>>& grid, int r, int c, int leftzeros, int m, int n) {
		if (leftzeros < 0 || r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == -1) {
			return 0;
		}
		if (grid[r][c] == 2) {
			return (leftzeros == 0); // if leftzeros == 0, found a way, otherwise not solution
		}
		// grid[r][c] = 0; at this moment
		leftzeros--;
		//int oldvalue = grid[r][c]; // 0 or 1 ? // should not keep 1
		grid[r][c] = -1; // mark it as visited !!!
		int paths = dfs_bf(grid, r + 1, c, leftzeros, m , n) + 
					dfs_bf(grid, r - 1, c, leftzeros, m , n) + 
					dfs_bf(grid, r, c + 1, leftzeros, m , n) + 
					dfs_bf(grid, r, c - 1, leftzeros, m , n) ;
		grid[r][c] = 0;
		return paths;
	}
};

int main() {
	vector<vector<int> > grid = {{1,0,0,0},{0,0,0,0},{0,0,0,2}};
	Solution s;
	cout << s.uniquePathsIII(grid) << endl;

	return 0;
}
