#include "common.h"
/*
 * There is a row of m houses in a small city, each house must be painted with one of the n colors
(labeled from 1 to n), some houses that has been painted last summer should not be painted again.

A neighborhood is a maximal group of continuous houses that are painted with the same color. (For
example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods  [{1}, {2,2}, {3,3}, {2}, {1,1}]).

Given an array houses, an m * n matrix cost and an integer target where:

    houses[i]: is the color of the house i, 0 if the house is not painted yet.
    cost[i][j]: is the cost of paint the house i with the color j+1.

Return the minimum cost of painting all the remaining houses in such a way that there are exactly
target neighborhoods, if not possible return -1.



Example 1:

Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
Output: 9
Explanation: Paint houses of this way [1,2,2,1,1]
This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
 */
class Solution {
  public:
    // https://leetcode.com/problems/paint-house-iii/discuss/674298/C%2B%2BPython-Simple-DP-top-down-bottom-up
    int minCost(vector<int> &houses, vector<vector<int>> &cost, int m, int n, int target) {
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(target + 1, vector<int>(n, INF)));
        // first m + 1 houses, groups == target, the last color is ?
        // first house
        // i == 0
        for (int c = 1; c <= n; ++c) {
            int &v = dp[0][1][c - 1];
            if (houses[0] == 0) {
                // not painted
                 v = cost[0][c - 1];
            } else {
                if (houses[0] == c) {
                    v = 0;
                } // else { // v = INF}
            }
        }
        for (int i = 1; i < m; ++i) {
            int upper = min(i + 1, target);    // at most this much neighbors
            for (int k = 1; k <= upper; ++k) { // neighbors
                for (int c = 1; c <= n; ++c) { // color it to c , markes as c-1
                    int &v = dp[i][k][c - 1];
                    if (houses[i] && c != houses[i]) {
                        // impossible, put it as INF;
                        continue;
                    } else {
                        // 1) houses[i] == 0 && c != houses[i]
                        // 2) houses[i] != 0 && c == houses 
                        int cost_same_group =
                            dp[i - 1][k][c - 1]; // make color of house[i] and hourse[i-1] to be same

                        int cost_diff_group = INF;
                        for (int pre_c = 1; pre_c <= n; ++pre_c) {
                            if (pre_c != c) {
                                cost_diff_group = min(cost_diff_group, dp[i - 1][k - 1][pre_c - 1]);
                            }
                        }
                        // need paint or not
                        int paint_cost = houses[i] == 0 ? cost[i][c - 1] : 0;
                        dp[i][k][c - 1] = min(cost_same_group, cost_diff_group) + paint_cost;
                    }
                }
            }
        }
        int r = *min_element(dp.back().back().begin(), dp.back().back().end());
        return r < INF ? r : -1;
    }

  private:
    const int INF = INT_MAX / 2;
};

int main() {

    vector<int> houses = {0, 0, 0, 0, 0};
    vector<vector<int>> cost = {{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}};
    int m = 5, n = 2, target = 3; // 9
    houses = {0,2,1,2,0}, cost = {{1,10},{10,1},{10,1},{1,10},{5,1}}, m = 5, n = 2, target = 3; // 11
    houses = {0,0,0,0,0}, cost = {{1,10},{10,1},{1,10},{10,1},{1,10}}, m = 5, n = 2, target = 5; // 5
    houses = {3,1,2,3}, cost = {{1,1,1},{1,1,1},{1,1,1},{1,1,1}}, m = 4, n = 3, target = 3; // -1




    Solution s;
    cout << s.minCost(houses, cost, m, n, target) << endl;
    return 0;
}
