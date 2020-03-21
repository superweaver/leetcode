#include "../../common.h"
class Solution {
    /*
    1) call DFS(G) to compute finishing time u.f for each vertex u
	2) compute GT
	3) call DFS(G), but in the main loop of DFS, consider the vertices in order of decreasing u.f (computed in 1)
	4) output the vertices of each tree in depth-first forest formed in 3 as a separate strongly connected component
	*/
public:
	void initialize() {
		edges.clear();
		edges.resize(n);
		edges[0].push_back(1);
		edges[1] = {2, 4, 5};
		edges[2] = {3, 6};
		edges[3] = {2, 7};
		edges[4] = {0, 5};
		edges[5] = {6};
		edges[6] = {5, 7};
		edges[7] = {7};
	}
	vector<vector<int>> decomposeDirectedGraph() {
		initialize();
		vector<pair<int, int>> dstime(n, {0, 0}); // start time and finish time
		vector<int> color(n, 0); // all white
		int time = 0;
		vector<int> componet;
		// first DFS
		for (int i = 0; i < n; ++i) {
			if (color[i] == 0) {
				dfs(i, color, dstime, time, edges, 0, componet);
			}
		}
		// calculate transpose graph			
		vector<vector<int>> transposeEdges(n);	
		for (int u = 0; u < n; ++u) {
			auto & adj = edges[u];
			for(auto v : adj) {
				transposeEdges[v].push_back(u);
			}
		}
		// sort adj according to finish time, decreasing order
        for (auto& adj : transposeEdges) {
            sort(adj.begin(), adj.end(),
                 [dstime](int u, int v) { return dstime[u].second > dstime[v].second; });
        }
		// do second dfs
		color = vector<int>(n, 0);
		vector<pair<int, int>> dstime2(n, {0, 0}); // start time and finish time
		time = 0;
		vector<int> order;
		for (int i = 0; i < n; ++i) {
			order.push_back(i);
		}
		// reorder order
        sort(order.begin(), order.end(),
             [dstime](int u, int v) { return dstime[u].second > dstime[v].second; });
		vector<vector<int>> result;
		for (auto i : order) {
			if (color[i] == 0) {
				result.push_back({});
				dfs(i, color, dstime2, time, transposeEdges, 1, result.back());
			}
		}
		return result;
    }
private:
	// refer to Figure 22.9
	const int n = 8; // number of vertices
	vector<vector<int>> edges; // directed edges in graph
	void dfs(int start, vector<int>&color, vector<pair<int, int>>& dstime, int& time, const vector<vector<int>> edges, int index, vector<int>& componet) {
		time++;
		//record starting time of start node
		dstime[start].first = time;
		color[start] = 1;
		for (auto c : edges[start]){
			if (color[c] == 0) {
				dfs(c, color, dstime, time, edges, index, componet);
			}
		}
		time++;
		// record finish time of start node
		dstime[start].second = time;
		color[start] = 2;
		if (index == 1) {
			componet.push_back(start);
		}
	}
};

int main() {

	Solution s;
	auto r = s.decomposeDirectedGraph();
	for (auto&v : r) {
		displayvector(v);
	}

	return 0;
}
