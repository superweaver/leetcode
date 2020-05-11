#include "common.h"
#include <functional>
class Solution {
public:
  int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple) {
      vector<vector<int>> graph(n); // nodes are 0...n-1
      for (const auto &e : edges) {
          graph[e[0]].push_back(e[1]);
          graph[e[1]].push_back(e[0]);
      }
      // note, this is tree
      // dfs
      vector<bool> visited(n, false);
      visited[0] = true; // root
      function<int(int)> dfs = [&](int root) -> int {
          visited[root] = true;
          int cost = 0; // return necessary time spent to walk from root to its subtrees
          for (int c : graph[root]) {
              if (visited[c]) {
                  continue;
              }
              int sc = dfs(c);
              if (sc || hasApple[c]) {
                  // note !!! hasApple[c]
                  cost += sc + 2;
              }
          }
          return cost;
      };
      return dfs(0);
  }
  int minTime_bfs(int n, vector<vector<int>> &edges, vector<bool> &hasApple) {
      unordered_map<int, vector<int>> graph;
      for (const auto &e : edges) {
          graph[e[0]].push_back(e[1]);
          graph[e[1]].push_back(e[0]);
      }
      // BFS
      vector<vector<int>> q;
      q.push_back({0});

      vector<bool> visited(n, false);
      visited[0] = true;
      int total = accumulate(hasApple.begin(), hasApple.end(), 0);
      vector<int> parent(n, -1);
      vector<int> apples(n, 0);
      int fetch = 0;
      while (!q.empty()) {
          auto currentlevel = q.back();
          vector<int> nextlevel;
          for (size_t i = 0; i < currentlevel.size(); ++i) {
              // for(auto c : currentlevel) {
              const auto &c = currentlevel[i];
              fetch += hasApple[c];
              if (fetch == total) {
                  // processing and return
                  // handle parent == -1;
                  // BFS again
                  int result = 0;
                  // initilize
                  for (int i = q.size() - 1; i >= 0; --i) {
                      auto &level = q[i];
                      for (auto node : level) {
                          apples[node] += hasApple[node];
                          auto p = parent[node];
                          if (p >= 0) { // necessary
                              apples[p] += apples[node];
                              if (apples[node]) {
                                  result += 2; // go from child to parent
                              }
                          }
                      }
                  }
                  return result;
              }
              for (auto next : graph[c]) {
                  if (!visited[next]) {
                      visited[next] = true;
                      nextlevel.push_back(next);
                      parent[next] = c;
                  }
              }
          }
          q.push_back(move(nextlevel));
      }
      return 0;
  }
};

int main() {
    int n = 7; 
    vector<vector<int>> edges = {{0,1},{0,2},{1,4},{1,5},{2,3},{2,6}}; 
    vector<bool> hasApple = {false,false,true,false,false,true,false}; // 6

    n = 7, edges = {{0,1},{0,2},{1,4},{1,5},{2,3},{2,6}}, hasApple = {false,false,true,false,true,true,false}; // 8

    n = 3, edges = {{0,1}, {0, 2}}, hasApple = {true, false, false};
	Solution s;
    cout << s.minTime_bfs(n, edges, hasApple) << endl;
    cout << s.minTime(n, edges, hasApple) << endl;

	return 0;
}
