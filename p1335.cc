#include "common.h"
// https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1335-minimum-difficulty-of-a-job-schedule/
class Solution {
  public:
    int minDifficulty(vector<int> &jobDifficulty, int d) {
        // dp[i][j] is the minimum difficulty to schedule first i jobs in j days
        const int n = jobDifficulty.size();
        if (d > n) {
            return -1; // no solution
        }
        vector<vector<int>> dp(n + 1, vector<int>(d + 1, INT_MAX / 2));
        // base i== 0
        dp[0][0] = 0;
        // transition
        // dp[i][k] = min(dp[j][k-1] + max(jobDifficulty[j..i-1]))
        // j >= k-1 && j <= i-1
        //
        // return dp[n][d]
        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k <= d; ++k) {
                int maxdiff = 0; // max diffculty of kth day
                for (int j = i - 1; j >= k - 1; --j) {
                    // j is the starting job index of kth day
                    maxdiff = max(maxdiff, jobDifficulty[j]);
                    dp[i][k] = min(dp[j][k - 1] + maxdiff, dp[i][k]);
                }
            }
        }
        return dp[n][d];
    }
};
class Solution_my {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        vector<vector<int>> dp(n + 1, vector<int>(d + 1, -2)); // not solved
        // dp[i][j] is the minimum difficulty of job sechdule for jobs [i...n-1], while
        // remaing days is j
        // return dp[0][d]
        // base case
        // dp[n][*] = 0;
        dp[n].assign(d + 1, 0);
        return helper(0, d, jobDifficulty, dp, n);
    }
private:
  int helper(int index, int d, vector<int> &jobDifficulty, vector<vector<int>> &dp, int n) {
      if (d == 0) {
          return 0;
      }
      if (d == 1) {
          int result = INT_MIN;
          for (int i = index; i < n; ++i) {
              result = max(jobDifficulty[i], result);
          }
          if (result == INT_MIN) {
              return dp[index][d] = -1;
          } else {
              return dp[index][d] = result;
          }
      }
      int days = n - index;
      if (d > days) {
          return dp[index][d] = -1;
      }
      if (dp[index][d] >= -1) { // calculated
          return dp[index][d];
      }
      int maxdiff = INT_MIN; // max difficulty of today's jobs
      int result = INT_MAX;
      for (int i = index; i < n; ++i) {
          maxdiff = max(maxdiff, jobDifficulty[i]);
          int rightDiff = helper(i + 1, d - 1, jobDifficulty, dp, n);
          if (rightDiff >= 0) {
              result = min(result, maxdiff + rightDiff);
          } else {
              break;
          }
      }
      if (result == INT_MAX) {
          return dp[index][d] = -1;
      } else {
          return dp[index][d] = result;
      }
  }
};

int main() {
    vector<int>jobDifficulty = {6,5,4,3,2,1};
    int d = 2; //7
    jobDifficulty = {9,9,9}, d = 4; //-1
    jobDifficulty = {1,1,1}, d = 3; //3
    jobDifficulty = {7,1,7,1,7,1}, d = 3; // 15
    jobDifficulty = {11,111,22,222,33,333,44,444}, d = 6;


	Solution s;
    cout << s.minDifficulty(jobDifficulty, d) << endl;

	return 0;
}
