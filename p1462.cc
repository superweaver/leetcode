#include "common.h"
class Solution {
public:
  vector<bool> checkIfPrerequisite(int n, vector<vector<int>> &prerequisites,
                                   vector<vector<int>> &queries) {
      // can optimize
      vector<vector<int>> graph(n);
      for (auto &p : prerequisites) {
          graph[p[0]].push_back(p[1]);
      }
      // topological sort
      vector<vector<int>> dp(n, vector<int>(n, 0));
      for (int i = 0; i < n; ++i) {
          dp[i][i] = 1;
      }
      // dp[i][j] = 1; i is prerequisite of j
      // dp[i][j] = 0; i is not a prerequisite of j
      vector<int> color(n, 0);
      vector<int> reverseOrder;
      for (int i = 0; i < n; ++i) {
          if (color[i] == 0) {
              dfs(color, graph, reverseOrder, i, dp);
          }
      }
      vector<bool> result;
      for (auto &q : queries) {
          result.push_back(dp[q[0]][q[1]]);
      }
      return result;
  }

  private:
    int dfs(vector<int> &color, vector<vector<int>> &graph, vector<int> &reverseOrder, int start,
            vector<vector<int>> &dp) {
        int n = color.size();
        if (color[start] == 2) {
            return start; //index in dp
        }
        // if (color[start] == 1) { // circle; }
        // color[start] = 0;
        color[start] = 1;
        for (auto next : graph[start]) {
            auto r = dfs(color, graph, reverseOrder, next, dp);
            auto&v = dp[r];
            for (int i = 0; i < n; ++i) {
                if (v[i]) {
                    dp[start][i] = 1;
                }
            }
        }
        color[start] = 2;
        reverseOrder.push_back(start);
        return start;
    }
};

int main() {
    int n = 2;
    vector<vector<int>> prerequisites{{1, 0}};
    vector<vector<int>> queries{{0, 1}, {1, 0}};

    Solution s;
    displayvector(s.checkIfPrerequisite(n, prerequisites, queries));

	return 0;
}
