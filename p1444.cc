#include "common.h"
class Solution {
  public:
    int ways(vector<string> &pizza, int k) {
        // each piece contains at least one apple.
        k--; // cut
        int m = pizza.size();
        int n = pizza[0].size();
        dp = move(
            vector<vector<vector<int>>>(k + 1, vector<vector<int>>(m, vector<int>(n, -1)))); // ways
        sum = move(vector<vector<int>>(m + 1, vector<int>(n + 1, 0))); // sum of apple
        // dp[k][i][j]
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                sum[i][j] =
                    (pizza[i][j] == 'A') + sum[i][j + 1] + sum[i + 1][j] - sum[i + 1][j + 1];
            }
        }
        return helper(k, 0, 0, m, n);
    }

  private:
    vector<vector<vector<int>>> dp;
    vector<vector<int>> sum; // sum[i][j] is the sum of apples from (i, j) -> (m-1, n-1)
    const int Mod = 1e9 + 7;
    int helper(int k, int r, int c, int m, int n) {
        if (dp[k][r][c] >= 0) {
            return dp[k][r][c];
        }

        if (sum[r][c] == 0) {
            return dp[k][r][c] = 0;
        }

        if (k == 0) {
            return dp[k][r][c] = sum[r][c] > 0;
        }

        dp[k][r][c] = 0;
        for (int i = r + 1; i < m; ++i) {
            if (sum[r][c] > sum[i][c]) {
                auto v = helper(k - 1, i, c, m, n);
                if (v == 0) {
                    break;
                } else {
                    dp[k][r][c] += v;
                    dp[k][r][c] %= Mod;
                }
            }
        }
        for (int j = c + 1; j < n; ++j) {
            if (sum[r][c] > sum[r][j]) {
                auto v = helper(k - 1, r, j, m, n);
                if (v == 0) {
                    break;
                } else {
                    dp[k][r][c] += v;
                    dp[k][r][c] %= Mod;
                }
            }
        }
        return dp[k][r][c] %= Mod;
    }
};

int main() {
    vector<string> pizza = {"A..","AAA","..."}; // 3
    int k = 3;

    //pizza = {"A..","AA.","..."}, k = 3; // 1
    //pizza = {"A..","A..","..."}, k = 1; // 1



	Solution s;
    cout << s.ways(pizza, k) << endl;

	return 0;
}
