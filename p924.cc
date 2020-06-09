#include "common.h"
struct UF {
	UF(int n) {
		groups = n;
		sizes = vector<int>(n, 1);
		parents.clear();
		for (int i = 0; i < groups; ++i) {
			parents.push_back(i);
		}
	}
	int Find(int i) {
		while (i != parents[i]) {
			parents[i] = parents[parents[i]];
			i = parents[i];
		}
		return i;
	}
	void Union(int u, int v) {
		int uid = Find(u);
		int vid = Find(v);
		if (uid == vid) {
			return;
		}
		int& usize = sizes[uid];
		int& vsize = sizes[vid];
		if (vsize < usize) {
			usize += vsize;
			parents[vid] = uid;
		}
		else {
			vsize += usize;
			parents[uid] = vid;
		}
		groups--;
	}
	int getgroups() {
		return groups;
	}
	int getsize(int node) {
		int id = Find(node);
		return sizes[id];
	}
private:
	vector<int> parents;
	vector<int> sizes;
	int groups;
};
class Solution {
public:
	int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
		int n = graph.size();
		int N = n * n;
		UF uf(n);
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
                if (graph[i][j]) { // on original graph
                    uf.Union(i, j);
                }
            }
		}

		int groups = uf.getgroups();
		unordered_map<int, pair<int, int>> cache; // root node -> <sizes, min_node>
		for (auto i : initial) {
			int root = uf.Find(i);
			if (!cache.count(root)) {
				cache[root] = {-uf.getsize(i), i};
			}
			else {
                // because there are more than 1 infected node in this connected component
                // this connected component will be infected
				cache[root] = { 0, min(i, cache[root].second) };
			}
		}
		auto result = cache.begin()->second;
		for (auto& p : cache) {
			result = min(result, p.second);
		}
		return result.second;
	}
};

int main() {

	Solution s;

	return 0;
}
