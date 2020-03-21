#include "../../../common.h"
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
        vector<pair<int, pair<int, int>>> prim()
        {
			/*
			 * MST-PRIM(G, w, r)
				for each u in G.V
					u.key = INF
					u.pi = NIL
				r.key = 0	// to be firstly checked out
				Q = G.V		// put all vertices into Q
				while Q is not empty
					u = EXTRAC-MIN(Q)
					for each v in G.adj(u)
					// update v’s pi and v’s key
					if v in Q and w(u, v) < v.key
						v.pi = u
						v.key = w(u, v)
			 */
            vector<pair<int, pair<int, int>>> result;
            initialize();
			int root = 0;
			vector<vector<pair<int, int>>> edges(d_size);
			for (auto& e : d_edges) {
				int weight = e.first;
				int u = e.second.first;
				int v = e.second.second;
				edges[u].push_back({v, weight});
				edges[v].push_back({u, weight});
			}
			// Binary Heap // to be done
			//  chapter 6, page 165
			multiset<pair<int, int>> fakeheap;
			vector<int> parent(d_size, INT_MAX); // use INT_MAX as NIL
			vector<int> key(d_size, INT_MAX);
			vector<bool> inQ(d_size, true);
			vector<int> r;
			for (int i = 0; i < d_size; ++i) {
				fakeheap.insert({INT_MAX, i});
			}
			vector<int> order;
			vector<int> dist;
			fakeheap.erase(fakeheap.find({INT_MAX, root})); // root.key = 0;
			fakeheap.insert({0, root});
			key[root] = 0;
			while((int)order.size() < d_size) {
				auto p = *fakeheap.begin();
				fakeheap.erase(fakeheap.begin());
				int distance = p.first;
				int u = p.second;
				order.push_back(u);
				dist.push_back(distance);
				inQ[u] = false;
				for (auto &next: edges[u]) {
					auto v = next.first;
					if (inQ[v] && next.second < key[v]) {
						// remove original weight, v
						fakeheap.erase(fakeheap.find({key[v], v}));
						key[v] = next.second;
						fakeheap.insert({key[v], v});
						parent[v] = u;
					}
				}
			}
			for (int i = 1; i < d_size; ++i) {
				result.push_back({dist[i], {order[i-1], order[i]}});
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
	auto r = s.prim();
	for (auto &e : r) {
		cout << e.second.first  << " <-> " << e.second.second << " : " << e.first << endl;
	}
	return 0;
}
