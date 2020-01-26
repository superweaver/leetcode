#include "common.h"
class Solution {
    public:
        // method one
        int minMalwareSpread_one(vector<vector<int>>& graph, vector<int>& initial) {
            // brutal force + bfs
            // this can be modified to be used for dfs
            // https://www.cnblogs.com/grandyang/p/12228494.html
            unordered_set<int> infected(initial.begin(), initial.end());
            int index = -1;
            int count = INT_MAX;
            int n = graph.size();
            for(auto i : initial) {
                infected.erase(i);
                int c = bfs(graph, n, infected, i);
                if (c < count || (c == count && i < index)) {
                    count = c;
                    index = i;
                }
                infected.insert(i);
            }
            return index;
        }
        // method two
        // https://www.youtube.com/watch?v=TXAo8EA95U8
        // dfs to return the number of node which can only be affected by one source node
        int minMalwareSpread_two(vector<vector<int>>& graph, vector<int>& initial) {
            sort(initial.begin(), initial.end());
            unordered_set<int> mal(initial.begin(), initial.end());
            int n = graph.size();
            int count = -1;
            int index = -1;
            for (auto i : initial) {
                unordered_set<int> visited;
                visited.insert(i);
                int save = 0; // the number of nodes which can only be affected by source i
                for (int j = 0; j < n; ++j) {
                    if (i != j && graph[i][j] == 1) {
                        int tmp = dfs(j, mal, visited, graph, n);
                        if (tmp < 0){
                            continue;
                        }
                        save += tmp;
                    }
                }
                if (save > count) {
                    count = save;
                    index = i;
                }
            }
            return index;

        }
        // method three, union + find
        // https://www.acwing.com/solution/leetcode/content/583/
        int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
            unordered_set<int> mal(initial.begin(), initial.end());
            int n = graph.size();
            DJS uf(n);
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    if (!mal.count(i) && !mal.count(j) && graph[i][j] == 1) {
                        uf.Union(i, j);
                    }
                }
            }
            unordered_map<int, unordered_set<int>> root2source;
            // key is the root of connected component, value is the connected intial sources
            for (auto source : initial) {
                for (int i = 0; i < n; ++i) {
                    if (!mal.count(i) && graph[i][source] == 1) {
                        int root = uf.find(i);
                        root2source[root].insert(source);
                    }
                }
            }
            int index = INT_MAX; // !!!
            int count = INT_MIN;
            // note: root2source may be empty
            for(auto& p : root2source) {
                if (p.second.size() == 1) {
                    int root = p.first;
                    int size = uf.sizes[root];
                    if (count > size) {
                        continue;
                    }
                    count = size;
                    if (index > *p.second.begin()) {
                        index = *p.second.begin();
                    }
                }
            }
            return index == INT_MAX ? *min_element(initial.begin(), initial.end()) : index;
        }
    private:
        int bfs(vector<vector<int>>& graph, int n, unordered_set<int> infected, int initial_node) {
            // pass initial_node to avoid modification of graph
            // note: !!! here, infected is passed as value, not reference
            queue<int> q;
            for (auto i : infected) {
                q.push(i);
            }
            while (! q.empty()) {
                auto c = q.front();
                q.pop();
                for(int i = 0; i < n; ++i) {
                    if (i == initial_node || graph[c][i] != 1 || infected.count(i)) {
                        continue;
                    }
                    infected.insert(i);
                    q.push(i);
                }
            }
            return infected.size();
        }
        int dfs(int node, unordered_set<int>& mal, unordered_set<int>& visited, vector<vector<int>>& graph, int n) {
            if (visited.count(node)) {
                return 0;
            }
            visited.insert(node);
            if(mal.count(node)) {
                return -1;
            }
            int save = 1; // node itself, which is connected to the deleted source
            for (int i = 0; i < n; ++i) {
                if (i != node && graph[node][i] == 1) {
                    int tmp = dfs(i, mal, visited, graph, n);
                    if (tmp == -1) {
                        // there are some other sources connected to node
                        // so node will always be affected.
                        mal.insert(node);
                        return -1;
                    }
                    save += tmp;
                }
            }
            return save;
        }
        struct DJS {
            vector<int> sizes;
            DJS(int n) {
                groups = n;
                for(int i = 0; i < n; ++i) {
                    parents.push_back(i);
                }
                sizes = vector<int>(n, 1);
            }
            void Union(int u, int v){
                int uid = find(u);
                int vid = find(v);
                if (uid == vid) return;
                int& usize = sizes[uid];
                int& vsize = sizes[vid];
                if (usize < vsize) {
                    vsize += usize;
                    parents[uid] = vid;
                } else {
                    usize += vsize;
                    parents[vid] = uid;
                }
                groups--;
            }
            int find(int node) {
                while(node != parents[node]) {
                    parents[node] = parents[parents[node]];
                    node = parents[node];
                }
                return node;
            }

            private:
            vector<int> parents;
            int groups;
        };
};
int main() {
    vector<vector<int>> graph = {{1,1,0},{1,1,1},{0,1,1}};
    vector<int> initial = {0,1};
    graph = {{1,1,0},{1,1,0},{0,0,1}};
    initial= {0,1};

    graph = {{1,0,0,0,0,1,0},{0,1,1,0,0,0,0},{0,1,1,0,0,0,0},{0,0,0,1,0,0,0},{0,0,0,0,1,0,0},{1,0,0,0,0,1,0},{0,0,0,0,0,0,1}};
    initial = {4};
    graph = {{1,1,0},{1,1,1},{0,1,1}};
    initial = {0,1};
    Solution s;
    cout << s.minMalwareSpread(graph, initial) << endl;
    return 0;
}
