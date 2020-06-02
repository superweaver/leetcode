#include "common.h"
class Solution {
  public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K) {
        // dp[i][j][k] is lowest price from i to j with at most k stops
        // dp[i][j][k] = min(dp[i][m][k-1] + price[m][j]);
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(K + 1, INT_MAX)));
        vector<vector<pair<int, int>>> from_prices(n);
        for (auto &v : flights) {
            int from = v[0];
            int to = v[1];
            int price = v[2];
            from_prices[to].push_back({from, price});
        }
        return helper(from_prices, dp, src, dst, K);
    }

  private:
    int helper(const vector<vector<pair<int, int>>> &from_prices, vector<vector<vector<int>>> &dp,
               int src, int dst, int K) {
        if (src == dst) {
            return 0;
        }
        if (K < 0) {
            return -1;
        }

        if (dp[src][dst][K] != INT_MAX) {
            return dp[src][dst][K]; // calculated
        } else {
            int to = dst;
            int cost = INT_MAX;
            for (auto &p : from_prices[to]) {
                int from = p.first;
                int price = p.second;
                int precost = helper(from_prices, dp, src, from, K - 1);
                if (precost != -1) {
                    cost = min(cost, precost + price);
                }
            }
            if (cost != INT_MAX) {
                dp[src][dst][K] = cost;
            } else {
                dp[src][dst][K] = -1;
            }
            return dp[src][dst][K];
        }
    }
};

int main() {

    Solution s;

    return 0;
}
