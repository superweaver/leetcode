#include "common.h"
class Solution2 {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        /*
         *
        1 <= m <= n <= 3*10^4
        group.length == beforeItems.length == n
        -1 <= group[i] <= m-1
        0 <= beforeItems[i].length <= n-1
        0 <= beforeItems[i][j] <= n-1
        i != beforeItems[i][j]
        beforeItems[i] does not contain duplicates elements.
         */
        /*
         * one graph for group
         */

        // group : itemid -> groupid
        vector<vector<int>> graph(m);  // gid -> itemid
        for (int i = 0; i < n; ++i) {
            if (group[i] == -1) {
                graph.push_back({});
                group[i] = graph.size() - 1;
                graph[group[i]].push_back(i);
            } else {
                graph[group[i]].push_back(i);
            }
        }
        m = graph.size();

        vector<set<int>> ggraph(m); // gid -> next gid
        vector<set<int>> innergraph(n);
        for (int i = 0; i < n; ++i) {
           // i is the itemid
           int currentgid = group[i];
           auto &v = beforeItems[i];
           for (auto j : v) {
               int pregid = group[j];
               if (pregid != currentgid) {
                   ggraph[pregid].insert(currentgid);
               } else {
                   // graph for sorting in same group
                   innergraph[j].insert(i);
               }
           }
        }
        // sort gid
        vector<int> gvisited(m, 0);
        vector<int> gorder;
        for (int i = 0; i < m; ++i) {
            if (gvisited[i] == 0) {
                if (!dfs(i, gvisited, gorder, ggraph)) {
                    return {};
                }
            }
        }

        // sort inner of each group
        vector<int> visited(n, 0);
        for (auto& g : graph) {
            // g is group
            int size = g.size();
            vector<int> order;
            for (int i = 0; i < size; ++i) {
                // use g[i] , not i
                if (visited[g[i]] == 0) {
                   if(! dfs(g[i], visited, order, innergraph)) {
                       return {};
                   }
                }
            }
            reverse(order.begin(), order.end());
            g = order;
        }
        vector<int> result;
        for (int i = m - 1; i >= 0; --i) {
            result.insert(result.end(), graph[gorder[i]].begin(), graph[gorder[i]].end());
        }
        return result;
    }
private:
  bool dfs(int node, vector<int> &visited, vector<int> &order, vector<set<int>> &graph) {
      if (visited[node] == 2) {
          return true;
      }
      if (visited[node] == 1) {
          return false;
      }

      visited[node] = 1;
      for (auto next : graph[node]) {
          //if (visited[next] == 0) {
          if (!dfs(next, visited, order, graph)) {
              return false;
          }
          //}
     }
     visited[node] = 2;
     order.push_back(node);
     return true;
  }
};
	
class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
		// check if beforeItems formed a loop
		// topological sort
		for(auto&v : beforeItems) {
			sort(v.begin(), v.end());
		}
		vector<vector<int>> g(m);
		for (int i = 0; i < n; ++i) {
			if (group[i] == -1) {
				g.push_back({i}); // act as individual group
                group[i] = g.size() - 1;
            }else {
				g[group[i]].push_back(i);
			}
		}
		m = g.size();
		vector<int> gid;
		for (int i = 0; i < m; ++i) {
			gid.push_back(i);
		}
		unordered_map<int, vector<int>> ggraph; // gid->next groups
		for (int i = 0; i < m; ++i) {
			unordered_set<int> before;
			unordered_map<int, vector<int>> graph; // start->others
			////////////////unordered_set<int> gi(g[i].begin(), g[i].end());
			for (auto j : g[i]) {
                if (beforeItems[j].empty()) {
                    continue; 
				}
				// pick a segment in range of g[i]		
				// others should be put into before
				for (auto k : beforeItems[j]) {
					auto it = lower_bound(g[i].begin(), g[i].end(), k);
					if (k < g[i].front() || k > g[i].back() || (*it != k)) {
                        before.insert(k);
                    } else {
                        graph[k].push_back(j);
                        // gi.count(k)
                    }
                }
            }
            auto r = helper(graph, g[i]);  // sort inside group
            if (!r) {
                return {};
            }
            unordered_set<int> gbefore;
            for (auto b : before) {
                gbefore.insert(group[b]);
            }
            for (auto gb : gbefore) {
                ggraph[gb].push_back(i);
            }
        }
        // the sort groups
		auto r = helper(ggraph, gid);
		if (!r) {
			return {};
		}
		vector<int> result;
		for (auto i : gid) {
			result.insert(result.end(), g[i].begin(), g[i].end());
		}
		return result;
    }
private:
	bool helper(unordered_map<int, vector<int>>&graph, vector<int>& nodes) {
		if (nodes.size() <= 1) {
			return true;
		}
        unordered_map<int, int> indegrees;
		for(auto i : nodes) {
			indegrees[i] = 0;
		}
		for (auto &p : graph) {
			for(auto node: p.second) {
				indegrees[node]++;
			}
		}
		set<pair<int, int>> s;
		for(auto &p : indegrees) {
			s.insert({p.second, p.first}); // indegree, node
		}
		vector<int> result;
		unordered_set<int> visited;
		while(!s.empty()) {
			auto top = *s.begin();
			int node = top.second;
			s.erase(s.begin());
			result.push_back(node);
			visited.insert(node);

			auto&v = graph[node];
            if (v.empty()) {
                continue;
            } else {
				for (auto next: v)  {
					if (visited.count(next)) {
						return false;
					}
					pair<int, int> pnext = {indegrees[next], next};
					s.erase(pnext);
					pnext.first--;
					indegrees[next]--;
					s.insert(pnext);
				}
            }
        }
		result.swap(nodes);
		return true;
    }
};

int main() {
    int n = 8;
    int m = 2;
    vector<int> group = { -1, -1, 1, 0, 0, 1, 0, -1 };
    vector<vector<int>> beforeItems = { {}, { 6 }, { 5 }, { 6 }, { 3, 6 }, {}, {}, {} };

	n = 8, m = 2, group = {-1,-1,1,0,0,1,0,-1}, beforeItems = {{},{6},{5},{6},{3},{},{4},{}}; // {}

    //n = 5, m = 5, group = { 2, 0, -1, 3, 0 };
    //beforeItems = { { 2, 1, 3 }, { 2, 4 }, {}, {}, {} };

    //Solution s;
	//displayvector(s.sortItems(n, m, group, beforeItems));

    //n = 5, m = 5, group = { 2, 0, -1, 3, 0 };
    //beforeItems = { { 2, 1, 3 }, { 2, 4 }, {}, {}, {} };
    Solution2 s2;
	displayvector(s2.sortItems(n, m, group, beforeItems));

	return 0;
}
