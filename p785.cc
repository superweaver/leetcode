#include "common.h"
class Solution {
public:
	bool isBipartite(vector<vector<int>>& graph) {
		int n = graph.size();
		vector<int> visited(n, 0);
		int part = -1; // -1 or -2 // use this as flag
		for (int i = 0; i < n; ++i) {
			if (visited[i] == 0) {
				bool r = dfs(graph, i, part, visited);
				if (!r) return false;
			}
		}
		return true;
	}
private:
	bool dfs(vector<vector<int>>& graph, int start, int part, vector<int>&visited) {
		if (visited[start] != 0) { 
            // visited[start] is what we had
            // part is what is expected
            // if they are different, return false
			return visited[start] == part;
		}
		visited[start] = part;
		for (auto i : graph[start]) {
			bool r = dfs(graph, i, -(3 + part), visited);
			if (!r) {
				return false;
			}
		}
		return true;
	}
};

int main() {

	Solution s;

	return 0;
}
