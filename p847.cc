#include "common.h"
// Return the length of the shortest path that visits every node.
// note: there is no length of each edge
// return the number of edges in the path of shortest node;
// 1 <= graph.length <= 12
// https://www.cnblogs.com/grandyang/p/11410007.html
class Solution {
  public:
    int shortestPathLength(vector<vector<int>> &graph) {
        // note 1 <= graph.length <= 12
        // BFS
        int step = 0;
        // initial state is all the nodes themselves (one hot)
        // final state is 2^n-1, n = graph.size(); all nodes are included;
        int n = graph.size();
        int target = (1 << n) - 1;
        unordered_set<int> visited;
        queue<pair<int, int>> q; // last node and current state
        for (int i = 0; i < n; ++i) {
            int state = 1 << i;
            int key = (state << 16) + i;
            visited.insert(key);
            q.push({i, state});
        }
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto p = q.front();
                q.pop();
                int lastnode = p.first;
                int state = p.second;
                if (state == target) {
                    return step;
                }
                for (auto neighbor : graph[lastnode]) {
                    int newstate = state | (1 << neighbor);
                    // // can't use state alone to mark visited or not
                    int key = (newstate << 16) + neighbor; // !!!
                    if (!visited.count(key)) {
                        visited.insert(key);
                        q.push({neighbor, newstate});
                    }
                }
            }
            step++;
        }
        return -1;
    }
};

// Return the length of the shortest path that visits every node.
// note: there is no length of each edge
// return the number of edges in the path of shortest node;
// 1 <= graph.length <= 12
// https://www.cnblogs.com/grandyang/p/11410007.html
class Solution_bfs2 {
  public:
    int shortestPathLength(vector<vector<int>> &graph) {
        int n = graph.size(), target = 0, res = 0;
        unordered_set<string> visited;
        queue<pair<int, int>> q;
        for (int i = 0; i < n; ++i) {
            int mask = (1 << i);
            target |= mask;
            visited.insert(to_string(mask) + "-" + to_string(i));
            q.push({mask, i});
        }
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                auto cur = q.front();
                q.pop();
                if (cur.first == target)
                    return res;
                for (int next : graph[cur.second]) {
                    int path = cur.first | (1 << next);
                    string str = to_string(path) + "-" + to_string(next);
                    if (visited.count(str))
                        continue;
                    visited.insert(str);
                    q.push({path, next});
                }
            }
            ++res;
        }
        return -1;
    }
};

int main() {

    Solution s;

    return 0;
}
