#include "common.h"
class Solution {
public:
    int minDistance(vector<int>& houses, int k) {
        sort(houses.begin(), houses.end());
        displayvector(houses);
        int n = houses.size();
        vector<int> prefix_sum(n+1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + houses[i];
        }
        // dp[i][j][k] is the minDistance we can get by assign k mailbox from hourse[i] to hourse[j]
        // min(dp[i][m][k-1] + dp[m+1][j][1])
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        return helper(houses, prefix_sum, dp, 0, n - 1, k);
    }
private:
  const int INF = INT_MAX / 2;
  int helper(vector<int> &houses, vector<int> &prefix_sum, vector<vector<vector<int>>> &dp,
             int start, int end, int k) {
      
      if (dp[start][end][k] >= 0) {
          return dp[start][end][k];
      }

      int len = end - start + 1;
      if (k >= len) {
          return dp[start][end][k] = 0;
      }

      if (k == 1) {

          // find the median of this segment
          // [2, 5] -> 3 instead of 3.5

          int median = (houses[start + len / 2] + houses[start + (len - 1) / 2]) / 2;
          // find first one  >= median
          auto it = lower_bound(houses.begin() + start, houses.begin() + end + 1, median);
          int med_indx = start + distance(houses.begin() + start, it);
          

          // find the sum of left
          // find the sum of right
          int leftsum = median * (med_indx - start) - (prefix_sum[med_indx] - prefix_sum[start]);
          int rightsum = (prefix_sum[end + 1] - prefix_sum[med_indx]) - median * (end + 1 - med_indx);
          return dp[start][end][k] =  leftsum + rightsum;
      } 
      int n = houses.size();
      int r = INT_MAX;
      for (int m = start; m < end; ++m) {
          r = min(r, helper(houses, prefix_sum, dp, start, m, k - 1) +
                         helper(houses, prefix_sum, dp, m + 1, end, 1));
      }
      return dp[start][end][k] = r;
  }
};

class Solution2 {
  public:
    int dp[101][101] = {};
    int dfs(vector<int> &h, vector<vector<int>> &costs, int i, int k) {
        if (i >= h.size() || k <= 0)
            return i == h.size() && k == 0 ? 0 : 10000000;
        if (!dp[i][k]) {
            dp[i][k] = 10000000;
            for (auto j = i; j <= h.size() - k; ++j)
                dp[i][k] = min(dp[i][k], costs[i][j] + dfs(h, costs, j + 1, k - 1));
        }
        return dp[i][k];
    }
    int minDistance(vector<int> &h, int k) {
        sort(begin(h), end(h));
        vector<vector<int>> costs(h.size(), vector<int>(h.size()));
        for (auto i = 0; i < h.size(); ++i) {
            for (auto j = i; j < h.size(); ++j) {
                int mbold = h[(i + j - 1) / 2], mbnew = h[(i + j) / 2];
                costs[i][j] =
                    (j == 0 ? 0 : costs[i][j - 1]) + h[j] - mbnew + (mbnew - mbold) * (j - i) % 2;
            }
        }
        return dfs(h, costs, 0, k);
    }
};

int main() {
    vector<int>houses = {1,4,8,10,20};
    int k = 3; // 5
    houses = {2, 3, 5, 12, 18}, k = 2; // 9
    houses = {7,4,6,1}, k = 1; // 8
    houses = {3,6,14,10}, k = 4; // 0

    houses = {9, 6, 17, 30, 27, 22, 20, 21, 1, 11}, k = 5; // 10

    Solution s;
    cout << s.minDistance(houses, k) << endl;
    Solution2 s2;
    cout << s2.minDistance(houses, k) << endl;


	return 0;
}
