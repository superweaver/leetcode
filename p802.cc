#include "common.h"
class Solution {
public:
	vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
		int n = graph.size();
		vector<int> state(n, 0); // 0 : unvisited; 1 : being visited ; >=2 visited
		for (int i = 0; i < n; ++i) {
			if (state[i] == 0) {
				dfs(graph, state, i);
			}
		}
		vector<int> result;
		for (int i = 0; i < n; ++i) {
			if (state[i] == 2) {
				result.push_back(i);
			}
		}
		return result;
	}
private:
	bool dfs(vector<vector<int> >&graph, vector<int>& state, int start){
		if (state[start] == 1) { // there is a loop
			return false;
		}
		if (state[start] == 2) {
			return true;
		}
		if (state[start] == 3) {
			return false;
		}
		state[start] = 1;
		bool r = true;
		for (auto n : graph[start]) {
			r &= dfs(graph, state, n);
		}
		if (r) {
			state[start] = 2;// visited and it is a safe node
		}
		else {
			state[start] = 3; // visited and it is not a safe node;
		}
		return r;
	}
};

int main() {

	Solution s;

	return 0;
}
