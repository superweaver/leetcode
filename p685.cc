#include "common.h"

class Solution {
public:
		vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {

		//https://www.youtube.com/watch?v=lnmJT5b4NlM
		if (edges.empty()) {
			return{};
		}
		int N = edges.size();
		// there are three cases
		//(1)	vector<vector<int> > edges = { {1,2}, {1,3}, {2,3} }; // no loop  but there is one node with two parents(indegree = 2)
		// (2) edges = { {1, 2}, { 2,3 }, { 3,4 }, { 4,1 }, { 1,5 } }; // has loop, no node with two parents
		//(3)	edges= { {2, 1}, { 3,1 }, { 4,2 }, { 1,4 }};          // has loop, has one node with two parents
		// for case (1), (3), there are only two candidates, cases two is equivalent to un-directed case
		vector<int> parents(N + 1, 0);
		vector<int> roots(N + 1, 0);
		vector<int> sizes(N + 1, 1);
		vector<int> candidate1, candidate2;
		vector<int> back;
		vector<int>* ref = nullptr;
		for (auto& e : edges) {
			int u = e[0];
			int v = e[1];
			if (!roots[u]) {
				roots[u] = u;
			}
			if (!roots[v]) {
				roots[v] = v;
			}
			if (parents[v] > 0) {
				// some other node has lead to v
				candidate1 = { parents[v], v };
				candidate2 = e;
				// trick; delete second candidate
				// if the remaining nodes form loop, then union-find can find the candidate1 or testing edge
				// if the remaining nodes don't form loop, then union-find can find it,  return candidate2;
				e[0] = e[1] = -1;
				ref = &e;
				back = e;
			}

			parents[v] = u;
		}
		for (auto & e : edges) {
			int u = e[0];
			int v = e[1];
			if (u < 0) continue; // deleted
			int uid = find(u, roots);
			int vid = find(v, roots);

			if (uid == vid) {
				if (!candidate1.empty()) {
					// case (3)
					return candidate1;
				}
				else {
					// case (2)
					return e;
				}
			}

			// union
			if (sizes[uid] < sizes[vid]) {
				roots[uid] = roots[vid];
				sizes[vid] += sizes[uid];
			}
			else {
				roots[vid] = roots[uid];
				sizes[uid] += sizes[vid];
			}
		}
		if (ref) {
			*ref = back;
		}
		// case(1)
		return candidate2;
	}
private:
	int find(int node, vector<int>& roots) {
		while (node != roots[node]) {
			roots[node] = roots[roots[node]];
			node = roots[node];
		}
		return node;
	}
};

int main() {

	Solution s;

	return 0;
}
