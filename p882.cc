#include "common.h"
// https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/discuss/156739/C%2B%2BJavaPython-Dijkstra-%2B-Priority-Queue
//
/*
 * intuition:
Store edges to another 2D hashtable e, so that we can easier get length between two node by e[i][j].
seen[i] means that we can arrive at node i and have seen[i] moves left.

We use a dijkstra algorithm in this solution.
Priority queue pq store states (moves left, node index).
So every time when we pop from pq, we get the state with the most moves left.

In the end, we calculate the number of nodes that we can reach.

res = seen.length
For every edge e[i][j]:
res += min(seen.getOrDefault(i, 0) + seen.getOrDefault(j, 0), e[i][j])
 */
class Solution {
  public:
    int reachableNodes(vector<vector<int>> edges, int M, int N) {
        unordered_map<int, unordered_map<int, int>> e; // 2d cache
        for (auto v : edges) {
            e[v[0]][v[1]] = e[v[1]][v[0]] = v[2];
        }
        priority_queue<pair<int, int>> pq; // (moves left, node index).
        // start point
        pq.push({M, 0});

        unordered_map<int, int> seen; // node : moves left
        // initially, no node was put into it

        while (!pq.empty()) {
            int moves = pq.top().first; // how many moves left
            int i = pq.top().second;    // current node index
            pq.pop();

            if (!seen.count(i)) {
                seen[i] = moves;
                for (auto j : e[i]) {
                    int moves2 = moves - j.second - 1;
                    if (!seen.count(j.first) && moves2 >= 0) {
                        pq.push({moves2, j.first});
                    }
                }
            }
        }
        int res = seen.size();
        for (auto v : edges) {
            int a = seen.find(v[0]) == seen.end() ? 0 : seen[v[0]];
            int b = seen.find(v[1]) == seen.end() ? 0 : seen[v[1]];
            // nice !!!
            res += min(a + b, v[2]);
        }
        return res;
    }
    int reachableNodes_my(vector<vector<int>> &edges, int M, int N) {
        unordered_map<int, int> cache; // key = i*N +j; val is how many new inserted nodes can be
                                       // visited from i to j direction
        unordered_map<int, vector<pair<int, int>>> Edges;
        int newNodes = 0;
        // some node may not be reachable from node 0;
        for (auto &v : edges) {
            Edges[v[0]].push_back({v[1], v[2]});
            Edges[v[1]].push_back({v[0], v[2]});
            newNodes += v[2];
        }
        /*
        for (int i = 0; i < N; ++i) {
            for (auto&p : Edges[i])
                cout << i << "->" << p.first << "=" << p.second << endl;
        }

        cout << endl;
        */
        vector<int> state(N, 0);
        state[0] = 1;
        vector<int> distance(N, INT_MAX);
        distance[0] = 0;
        // only mark original node

        // how many connected nodes with 0
        int connected = 1;
        vector<int> currentlayer;
        currentlayer.push_back(0);
        while (!currentlayer.empty()) {
            vector<int> nextlayer;
            for (auto c : currentlayer) {
                for (auto &v : Edges[c]) {
                    if (state[v.first] == 0) {
                        state[v.first] = 1;
                        nextlayer.push_back(v.first);
                        connected++;
                    }
                }
            }
            currentlayer.swap(nextlayer);
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

        q.push({0, 0}); // distance and index of node
        int visited = 1;
        vector<bool> Visited(N, false);
        while (!q.empty()) {
            auto p = q.top();
            q.pop();
            int current = p.second;
            if (Visited[current])
                continue;
            int steps = M - p.first;
            for (auto &next : Edges[current]) {
                int need = next.second;
                int nextnode = next.first;
                if (steps > need) {
                    q.push({p.first + need + 1, nextnode});
                    if (distance[nextnode] == INT_MAX) {
                        visited++;
                    }
                    distance[nextnode] = min(distance[nextnode], p.first + need + 1);
                }
            }
            Visited[current] = true;
            if (visited == connected) {
                //	break;
            }
        }
        // extend from  original node
        for (int i = 0; i < N; ++i) {
            if (distance[i] <= M) {
                int steps = M - distance[i];
                if (steps == 0)
                    continue;
                int current = i;
                for (auto &next : Edges[current]) {
                    int need = next.second;
                    int nextnode = next.first;
                    int key_c2n = current * N + nextnode;
                    // int key_n2c = nextnode * N + current;
                    if (steps >= need) {
                        cache[key_c2n] = need;
                    } else {
                        cache[key_c2n] = steps;
                    }
                    //	cout << current << "->" << nextnode << "=" << cache[key_c2n] << endl;
                }
            }
        }
        int result = visited;
        for (auto &v : edges) {
            int key1 = v[0] * N + v[1];
            int key2 = v[1] * N + v[0];
            int v1 = cache.count(key1) ? cache[key1] : 0;
            int v2 = cache.count(key2) ? cache[key2] : 0;
            result += min(v1 + v2, v[2]);
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
