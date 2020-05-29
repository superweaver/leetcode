#include "common.h"

class Solution {
  public:
    int networkDelayTime(vector<vector<int>> &times, int N, int K) {
        const int MAX = numeric_limits<int>::max();

        vector<vector<pair<int, int>>> graph(N + 1);

        for (vector<int> &edge : times) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }

        vector<bool> visited(N + 1, false);
        vector<int> distances(N + 1, MAX);
        distances[K] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
        queue.push({0, K}); // arrival time and index of node;
        while (!queue.empty()) {
            pair<int, int> cur = queue.top();
            queue.pop(); // removed the shortest time

            if (visited[cur.second]) { // there is an earlier arraival time, this is a later time,
                                       // no need to consider it any more
                continue;
            }
            for (pair<int, int> &n : graph[cur.second]) {
                if (distances[n.first] > distances[cur.second] + n.second) {
                    distances[n.first] = distances[cur.second] + n.second; // update time
                    queue.push({distances[n.first], n.first});
                }
            }
            visited[cur.second] = true;
        }
        int res = *max_element(distances.begin() + 1, distances.end());
        return res == MAX ? -1 : res;
    }
};

class Solution2 {
  public:
    int networkDelayTime(vector<vector<int>> &times, int N, int K) {
        std::vector<std::vector<std::pair<int, int>>> graph(N);
        for (int i = 0; i < times.size(); i++) {
            int u = times[i][0] - 1;
            int v = times[i][1] - 1;
            int w = times[i][2];
            graph[u].push_back({v, w});
        }

        unordered_map<int, int> target_node; // index -> cost
        for (int i = 1; i <= N; i++) {
            if (i != K) {
                target_node[i - 1] = std::numeric_limits<int>::max();
            }
        }

        int res = 0;
        int node = K - 1; // current node
        int dis = 0;
        while (!target_node.empty()) {
            //更新距离
            for (int i = 0; i < graph[node].size(); i++) {
                int v = graph[node][i].first;
                int w = graph[node][i].second;
                auto it = target_node.find(v);
                if (it != target_node.end()) {
                    it->second = std::min(it->second, dis + w);
                } // otherwise, it has been determined
            }

            //找到剩下的点中距离最短的点
            // this should be by a priority queue
            auto min_dis = target_node.begin();
            for (auto it = target_node.begin(); it != target_node.end(); ++it) {
                if (it->second < min_dis->second) {
                    min_dis = it;
                }
            }

            node = min_dis->first;
            dis = min_dis->second;
            if (dis == std::numeric_limits<int>::max()) {
                return -1;
            }
            target_node.erase(min_dis);
        }
        return dis;
    }
};

class Solution3 {
    // fuck it , this is only useful for DAG :(
  public:
    int networkDelayTime(vector<vector<int>> &times, int N, int K) {
        // topological sort
        // and relaxation
        vector<int> color(N, 0);
        // vector<int> parent(N, INT_MAX);
        vector<int> time(N, INT_MAX);
        d_edges.resize(N);

        for (auto &v : times) {
            d_edges[v[0] - 1].push_back({v[1] - 1, v[2]});
        }
        K--; // to 0-index
        time[K] = 0; // important

        vector<int> reversedorder;
        for (int i = 0; i < N; ++i) {
            if (color[i] == 0) {
                dfs(i, color, reversedorder);
            }
        }
        displayvector(reversedorder, true);

        for (int i = reversedorder.size() - 1; i >= 0; --i) {
            // do relaxation
            int u = reversedorder[i];

            int candidate = time[u];
            if (candidate != INT_MAX) {
                for (auto &e : d_edges[u]) {
                    int v = e.first;
                    if (time[v] > candidate + e.second) {
                        time[v] = candidate + e.second;
                        // parent[v] = u;
                    }
                }
            }
        }
        displayvector(time);
        auto r = *max_element(time.begin(), time.end());
        return r == INT_MAX ? -1 : r;
    }

  private:
    vector<vector<pair<int, int>>> d_edges;
    void dfs(int start, vector<int> &color, vector<int> &reversedorder) {
        color[start] = 1;
        for (auto &e : d_edges[start]) {
            if (color[e.first] == 0) {
                dfs(e.first, color, reversedorder);
            }
        }
        reversedorder.push_back(start);
        color[start] = 2;
    }
};

int main() {
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int N = 4;
    int K = 2;
    times = {{1, 3, 68}, {1, 4, 20}, {4, 1, 65}, {3, 2, 74}, {2, 1, 44}, {3, 4, 61}, {4, 3, 68},
             {3, 1, 26}, {5, 1, 60}, {5, 3, 3},  {4, 5, 5},  {2, 5, 36}, {2, 3, 94}, {1, 2, 0},
             {3, 5, 90}, {2, 4, 28}, {4, 2, 12}, {5, 4, 52}, {5, 2, 85}, {1, 5, 42}};
    N = 5;
    K = 4;

    Solution s;
    cout << s.networkDelayTime(times, N, K) << endl;

    Solution2 s1;
    cout << s1.networkDelayTime(times, N, K) << endl;

    Solution3 s2;
    cout << s2.networkDelayTime(times, N, K) << endl;

    return 0;
}
