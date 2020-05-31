#include "common.h"
class Solution {
public:
  int minReorder(int n, vector<vector<int>> &connections) {
      // 2 <= n <= 5 * 10^4
      // dfs + bfs
      // nice question, hard to solve
      vector<vector<vector<int>>> graph(2, vector<vector<int>>(n)); // original graph, reverse graph
      for (auto &v : connections) {
          graph[0][v[0]].push_back(v[1]); // original graph
          graph[1][v[1]].push_back(v[0]); // reverse graph
      }

      vector<int> reachcity0(n, 0); // reachcity0[0] = 1; // can reach city 0
      vector<int> color(n, 0);
      bool dfsinoriginal = true;
      vector<int> current;
      current.push_back(0);

      result = 0;
      while(!current.empty()) {
          vector<int> next;
          for (auto i : current) {
              if (color[i] == 0) {
                  dfs(i, color,  graph, dfsinoriginal, next, reachcity0);
              }
          }
          dfsinoriginal = !dfsinoriginal;
          current.swap(next);
      }
      result--;
      return result;
  }

private:
  int result;
  void dfs(int start, vector<int> &color, vector<vector<vector<int>>> &graph, bool dfsinoriginal,
           vector<int> &next, vector<int> &reachcity0) {
      // no circle
      if (color[start] == 2) {
          return;
      }
      color[start] = 1;
      vector<vector<int>> &current = dfsinoriginal ? graph[0] : graph[1];
      vector<vector<int>> &reverse = dfsinoriginal ? graph[1] : graph[0];

      // add node in reverse graph into next
      for (auto neighbor : reverse[start]) {
          if (color[neighbor] == 0) {
              next.push_back(neighbor);
              if (dfsinoriginal) {
                  reachcity0[neighbor] = 1; // for neighbor in reverse graph
                  // no need to reorder these edges
              }
          }
      }

      for (auto node: current[start]) {
          dfs(node, color, graph, dfsinoriginal, next, reachcity0);
      }
      if (dfsinoriginal) {
          result++; // for start
          reachcity0[start] = 1;
      }
      color[start] = 2;
  }
};

int main() {
    int n = 6;
    vector<vector<int>> connections = {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}}; // 3
    n = 5, connections = {{1,0},{1,2},{3,2},{3,4}}; // 2
    n = 3, connections = {{1,0},{2,0}}; // 0
    n = 5; connections = {{1, 0}, {1, 2}, {2, 3}, {4, 2}}; // 2
    n = 4; connections = {{1, 0}, {2, 1}, {3, 2}}; // 0

    Solution s;
    cout << s.minReorder(n, connections) << endl;

	return 0;
}
