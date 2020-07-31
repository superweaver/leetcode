#include "common.h"
// https://leetcode.com/problems/pizza-with-3n-slices/discuss/546474/Python-Robber-n3-Houses-in-Cycle
// https://www.acwing.com/solution/LeetCode/content/10196/

class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        // this question is equivalent to
        // pick n elements from 3n elements, and none of these n elements are adjacent
        // case 1)
        // pick slices[0]
        // then slices.back() can't be picked
        //
        // this is equivalent to pick n elements from [0, 3*n-2]
        //
        // case 2)
        // don't pick slices[0]
        // then slices.back() can be picked
        // equivalent to pick n element from [1, 3*n-1];
        //
        // alternatively , we can set slices.back() = INT_MIN in case1;
        // and set slices[0] = INT_MIN in case2;

        int back = slices[0];
        slices[0] = INT_MIN; // trick
        int v1 = helper(slices);
        slices[0] = back;

        back = slices.back();
        slices.back() = INT_MIN; // trick
        int v2 = helper(slices);
        slices.back() = back;
        return max(v1, v2);
    }
private:
  int helper(vector<int> &slices) {
      int N = slices.size();
      int n = N / 3;
      int result = 0;
      // dp[i][j] is the max summation of j elements from first i elements from slices
      // dp[*][0] = 0;
      // dp[0][*] = 0;
      // case 1)
      // dp[i][j] = dp[i-1][j]; // don't use slices[i-1]
      // case 2) // use slices[i-1], then slices[i-2] can't be used
      // dp[i][j] = slices[i-1] + dp[i-2][j-1]
      vector<vector<int>> dp(N + 1, vector<int>(n + 1, 0));
      for (int i = 1; i <= N; ++i) {
          for (int j = 1; j <= n; ++j) {
              dp[i][j] = max(dp[i - 1][j], slices[i - 1] + (i >= 2 ? dp[i - 2][j - 1] : 0));
          }
      }
      return dp[N][n];
  }
};
int main() {
    vector<int> slices = {4,1,2,5,8,3,1,9,7}; // 21
    slices = {1,2,3,4,5,6};// 10
    slices = {8,9,8,6,1,1}; // 16
    slices = {3, 1, 2}; // 3

    Solution s;
    cout << s.maxSizeSlices(slices) << endl;
	return 0;
}
