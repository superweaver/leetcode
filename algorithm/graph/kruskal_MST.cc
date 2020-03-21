#include "../../../common.h"
/*
 MST-KRUSKAL(G, w)
A = empty
for each vertex v in G.V
	MAKE-SET(v)
sort the edges of G.E into non-decreasing order by weight w
for each edge (u, v) in G.E, taken in non-decreasing order by weight
	if FIND-SET(u) != FINT-SET(v)
		A = A union {(u, v)}
		UNION(u, v)
return A
*/
class DisjointSet{
	public:
		DisjointSet(int n) {
			parents.resize(n);
			for (int i = 0; i < n; ++i) {
				parents[i] = i;
			}
			sizes = vector<int> (n, 1);
		}
		int Find(int node) {
			while (node != parents[node]) {
				parents[node] = parents[parents[node]];
				node = parents[node];
			}
			return node;
		}
		bool isSameGroup(int u, int v) {
			return Find(u) == Find(v);

		}
		void Union (int u, int v) {
			int uid = Find(u);
			int vid = Find(v);
			if (uid == vid) {
				return ;
			}
			int& usize = sizes[uid];
			int& vsize = sizes[vid];
			if (usize < vsize) {
				vsize += usize;
				parents[uid] = vid;
			} else {
                usize += vsize;
                parents[vid] = uid;
            }
		}
	private:
		vector<int> parents;
		vector<int> sizes;
};
class Solution {
	public:
		void initialize() {
			// refer to Fig 23.4
			d_size = 9;
			d_edges.clear();
			/*
			 *
			d_edges.resize(n);
			d_edges[0] = {{1, 4}, {7, 8}}; // 2
			d_edges[1] = {{0, 4}, {2, 8}, {7, 11}}; // 3
			d_edges[2] = {{1, 8}, {8, 2}, {5,4}, {3, 7}}; //4 
			d_edges[3] = {{2, 7}, {4, 9}, {5, 14}}; //3
			d_edges[4] = {{3, 9}, {5, 10}}; // 2
			d_edges[5] = {{6, 2}, {4, 10}, {3, 14}, {2, 4}}; //4
			d_edges[6] = {{5, 2}, {7, 1}, {8, 6}}; // 3
			d_edges[7] = {{6, 1}, {8, 7}, {0, 8}, {1, 11}}; // 4
			d_edges[8] = {{7, 7}, {2, 2}, {6, 6}}; //3
			*/
            d_edges.push_back({ 4, { 0, 1 } });
            d_edges.push_back({ 8, { 1, 2 } });
            d_edges.push_back({ 7, { 2, 3 } });
            d_edges.push_back({ 9, { 3, 4 } });
            d_edges.push_back({ 10, { 4, 5 } });
            d_edges.push_back({ 2, { 5, 6 } });
            d_edges.push_back({ 1, { 6, 7 } });
            d_edges.push_back({ 7, { 7, 8 } });
            d_edges.push_back({ 8, { 0, 7 } });
            d_edges.push_back({ 11, { 1, 7 } });
            d_edges.push_back({ 2, { 2, 8 } });
            d_edges.push_back({ 6, { 6, 8 } });
            d_edges.push_back({ 4, { 2, 5 } });
            d_edges.push_back({ 14, { 3, 5 } });
        }
        vector<pair<int, pair<int, int>>> kruskal()
        {
            vector<pair<int, pair<int, int>>> result;
            initialize();
			sort(d_edges.begin(), d_edges.end());
			DisjointSet uf(d_size);
			for(auto &e : d_edges) {
				int u = e.second.first;
				int v = e.second.second;
				if (uf.isSameGroup(u, v)) {
					continue;
				} else {
					result.push_back(e);
					uf.Union(u, v);
				}
				
			}
			return result;
        }

	private:
        //vector<vector<pair<int, int>>> d_edges;
		vector<pair<int, pair<int, int>>> d_edges; // weight, <from, to> // only one direction is ok
		int d_size;

};
int main() {
	Solution s;
	auto r = s.kruskal();
	for (auto &e : r) {
		cout << e.second.first  << " <-> " << e.second.second << " : " << e.first << endl;
	}
	return 0;
}
