#include "common.h"
class Solution
{
  public:
	int minScoreTriangulation(vector<int> &A)
	{
		int n = A.size();
		A.push_back(A[0]);
		// assume there is an optimial way to get minScore
		// there vertex 0 must be along with another two vertices x and y
		// for this small triangle, the score is A[0] * A[x] * A[y]
		// this trangle divides all other vertices into extra three blocks
		// [0..X], [X, Y], [Y, 0]
		// solve sub problem to get dp[i][j]
		// for this partition, the result is dp[0][x]+dp[x][y]+dp[y][0] + A[0] * A[x] * A[y]
		// try every combinations, we can get minScores
		dp = vector<vector<int>>(n, vector<int>(n + 1, -1));
		int result = INT_MAX;
		for (int i = 1; i < n - 1; ++i) {
			for (int j = i + 1; j < n; ++j) {
				int score = A[0] * A[i] * A[j] + helper(0, i, A) + helper(i, j, A) + helper(j, 0 + n, A);
				result = min(score, result);
			}
		}
		A.pop_back();
		return result;
	}

  private:
	vector<vector<int>> dp;
	int helper(int start, int end, vector<int> &A) { 
		int len = end - start + 1;
		if (dp[start][end] >= 0) {
			return dp[start][end];
		}
		if (len < 3) {
			return dp[start][end] = 0;
		}
		if (len == 3) {
			int score = A[start] * A[start + 1] * A[end];
			return dp[start][end] = score;
		}
		// pick another one as third partition point
		int r = INT_MAX;
		for (int i = start + 1; i <= end - 1; ++i) {
			int score = A[start]* A[i] * A[end] + helper(start, i, A) + helper(i, end, A);
			r = min(score, r);
		}
		return dp[start][end] = r;
	}
};

int main()
{
	vector<int> A = {3,7,4,5}; // 144
	A = {1, 3, 1, 4, 1, 5};
	Solution s;
	cout << s.minScoreTriangulation(A) << endl;
	return 0;
}
