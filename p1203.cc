#include "common.h"
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

    n = 5, m = 5, group = { 2, 0, -1, 3, 0 };
    beforeItems = { { 2, 1, 3 }, { 2, 4 }, {}, {}, {} };

    Solution s;
	displayvector(s.sortItems(n, m, group, beforeItems));

	return 0;
}
