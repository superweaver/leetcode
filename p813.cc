#include "common.h"
//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-813-largest-sum-of-averages/

// Author: Huahua
// Running time: 9 ms
// nice
class Solution {
public:
  double largestSumOfAverages(vector<int>& A, int K) {
    const int n = A.size();

    // dp[i][j] is the max score you can get by dividing first j element into i groups (at most)
    // return dp[K][n]
    vector<vector<double>> dp(K + 1, vector<double>(n + 1, 0.0));
    vector<double> sums(n + 1, 0.0);
    for (int i = 1; i <= n; ++i) {
      sums[i] = sums[i - 1] + A[i - 1];
      dp[1][i] = static_cast<double>(sums[i]) / i;
    }

    for (int k = 2; k <= K; ++k) {
        for (int i = k; i <= n; ++i) {
            for (int j = k - 1; j < i; ++j) {
                dp[k][i] = max(dp[k][i], dp[k - 1][j] + (sums[i] - sums[j]) / (i - j));
            }
        }
    }
    return dp[K][n];
  }
};

class Solution_my {
  public:
    double largestSumOfAverages(vector<int> &A, int K) {
        int n = A.size();
        vector<int> prefixsum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixsum[i + 1] = prefixsum[i] + A[i];
        }
        vector<vector<vector<double>>> dp(n, vector<vector<double>>(n, vector<double>(K + 1, 0)));
        double r = 0;
        for (int k = K; k > 0; --k) {
            r = max(r, get(0, n - 1, k, A, dp, prefixsum));
        }
        return r;
    }
    double get(int left, int right, int k, vector<int> &A, vector<vector<vector<double>>> &dp,
               vector<int> &prefixsum) {
        if (left == right) {
            if (k == 1) {
                return A[left];
            } else {
                return 0;
            }
        }
        int len = right - left + 1;
        if (k > len) {
            return 0;
        }
        if (dp[left][right][k] > 0) {
            return dp[left][right][k];
        }
        if (k == 1) {
            return dp[left][right][k] = (prefixsum[right + 1] - prefixsum[left]) / double(len);
        }
        if (len == k) {
            return dp[left][right][k] = prefixsum[right + 1] - prefixsum[left];
        }
        for (int mid = right - 1; mid - left + 1 >= k - 1; --mid) {
            double l = get(left, mid, k - 1, A, dp, prefixsum);
            double r = get(mid + 1, right, 1, A, dp, prefixsum);
            dp[left][right][k] = max(dp[left][right][k], l + r);
        }
        return dp[left][right][k];
    }
};

int main() {

	Solution s;

	return 0;
}
