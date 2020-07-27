#include "common.h"
#include <functional>
// Author: Huahua
// https://zxi.mytechroad.com/blog/graph/leetcode-1192-critical-connections-in-a-network/
class Solution_hua {
  public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections) {
        vector<vector<int>> g(n);   // graph
        vector<int> ts(n, INT_MAX); // time stamp
        vector<vector<int>> ans;    // critical connections
        int t = 0;

        function<int(int, int)> tarjan = [&](int i, int p) {
            int min_i = ts[i] = ++t;
            for (int j : g[i]) {
                if (ts[j] == INT_MAX) {
                    int min_j = tarjan(j, i);
                    min_i = min(min_i, min_j);
                    if (ts[i] < min_j) {
                        ans.push_back({i, j});
                    }
                } else if (j != p) {
                    min_i = min(min_i, ts[j]);
                }
            }
            return min_i;
        };

        for (const auto &e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        tarjan(0, -1);
        return ans;
    }
};

class Solution {
  public:
    // https://blog.csdn.net/wtyvhreal/article/details/43530613
    // https://www.cnblogs.com/en-heng/p/4002658.html
    // https://www.cnblogs.com/nullzx/p/7968110.html
    // https://nagato1208.github.io/2019/09/15/leetcode-1192-Critical-Connections-in-a-Network-tarjan%E6%B1%82%E5%89%B2%E8%BE%B9/
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections) {
        // note original graph is connected
        vector<vector<int>> edges(n);
        for (auto &e : connections) {
            edges[e[0]].push_back(e[1]);
            edges[e[1]].push_back(e[0]); // !!!
        }
        vector<bool> visited(n, false);
        vector<bool> isCutVertex(n, false);
        vector<vector<int>> cutEdge;

        vector<int> low(
            n, 0); // the smallest timestamp a node u can get without going through its parent
        vector<int> dfn(n, 0);     // timestamp
        vector<int> parent(n, -1); //

        // start from node 0;
        visited[0] = true; // mark it as visted
        parent[0] = -1;
        int time = 0;
        dfn[0] = low[0] = time;

        int childTree = 0; // used to check if root ( node 0) is cut vertex
        for (auto next : edges[0]) {
            if (!visited[next]) {
                visited[next] = true;
                parent[next] = 0;
                dfs(next, edges, time, dfn, low, childTree, visited, parent, isCutVertex, cutEdge);
                // check if edge with root 0 is a cut edge/bridge
                if (low[next] > dfn[0]) {
                    cutEdge.push_back({0, next});
                }
                childTree++;
            }
        }
        if (childTree >= 2) {
            // root 0 is a cut vertex
            isCutVertex[0] = true;
        }
        return cutEdge;
    }

  private:
    void dfs(int v, vector<vector<int>> &edges, int &time, vector<int> &dfn, vector<int> &low,
             int &childTree, vector<bool> &visited, vector<int> &parent, vector<bool> &isCutVertex,
             vector<vector<int>> &cutEdge) {
        dfn[v] = low[v] = ++time; // timestamp
        for (auto w : edges[v]) {
            if (!visited[w]) {
                visited[w] = true;
                parent[w] = v;
                dfs(w, edges, time, dfn, low, childTree, visited, parent, isCutVertex, cutEdge);
                // update low[v] through its child
                low[v] = min(low[v], low[w]);
                // check if v is a cut vertex
                // v is cut vetext if at least one child statisfy low[w] >= dfn[v]
                // it means w can't get smaller time stamp without using parent v
                if (low[w] >= dfn[v]) {
                    isCutVertex[v] = true;
                    // check if v, w is a bridge
                    if (low[w] > dfn[v]) {
                        cutEdge.push_back({v, w});
                    } // else {// there is a way to make low[w] <= dfn[v], there is a back edge }
                }
            } else {
                // w has been visited
                // edge(v, w) is a back edge
                // pay attention to the defintion of low[v]
                // low[v] is the minimum of timestamp by not going through v's parent

                // so we need to check parent[v] != w
                // if (parent[v] != w && dfn[w] < dfn[v]) {
                if (parent[v] != w) {
                    low[v] = min(low[v], dfn[w]);
                }
            }
        }
    }
};

int main() {
    int n = 4;
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    n = 5;
    connections = {{1, 0}, {2, 0}, {3, 2}, {4, 2}, {4, 3}, {3, 0}, {4, 0}};

    Solution s;
    auto r = s.criticalConnections(n, connections);
    for (auto &p : r) {
        displayvector(p);
    }
    return 0;
}
