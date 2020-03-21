#include "../../common.h"
class Solution {
public:
    vector<string> steps{"shirt" , "tie", "jacket", "belt", "undershorts", "pants", "shoes", "socks", "watch"};
					//     0,		1,		2,		   3,		4,			5,		6,			7,		8
	vector<vector<int>> edges;
	void initialize() {
		edges.clear();
		edges.resize(steps.size());
		edges[0].push_back(1);
		edges[0].push_back(3);
		edges[1].push_back(2);
		edges[3].push_back(2);
		edges[4].push_back(5);
		edges[4].push_back(6);
		edges[5].push_back(3);
		edges[5].push_back(6);
		edges[7].push_back(6);
	}
	vector<string> toplogicalSort(){
        /*
         * TOPOLOGICAL -SORT
         *	1 call DFS(G) to compute finishing times f for each vertex
         *	2 as each vertex is finished, insert it onto the front of a linked list
         *	3 return the linked list of vertices
		 *	!!!! no need to count in-degrees and use priority_queue to sort them
         */
        displayvector(steps);
        vector<int> result;
        initialize();
		int n = steps.size();
		vector<int> color(n, 0); //0 -> white, 1-> gray, 2-> black
		vector<pair<int, int>> timestamp(n, {0, 0}); // start time, finish time
		int time = 0;
		for (int i = 0; i < n; ++i) {
			if (color[i] == 0) {
				dfs(i, edges, color, timestamp, time, result);
			}
		}
		reverse(result.begin(), result.end()); // !!! reversed order
		vector<string> r;
		for(auto i : result) {
			r.push_back(steps[i]);
		}
		displayvector(r);
		return r;
	}
private:
	void dfs(int u, const vector<vector<int>> edges,  vector<int>& color, vector<pair<int, int>>&timestamp, int& time, vector<int>& result) {
		time++;
		timestamp[u].first = time;
		// if color[u] == 1, then there is a cycle
		color[u] = 1; // gray;
		for (auto v : edges[u]) {
			if (color[v] == 0) {
				dfs(v, edges, color, timestamp, time, result);
			}
		}
		time++;
		timestamp[u].second = time;
		color[u] = 2; // black
		result.push_back(u);
	}
};

int main() {

	Solution s;
	s.toplogicalSort();
	return 0;
}
