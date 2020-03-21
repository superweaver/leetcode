#include "../../../common.h"
class Solution{
	public:
		/*
		DIJKSTRA(G, w, s)
		INITIALIZE-SINGLE_SOURCE(G,s)
		S = empty
		Q = G.V
		while Q != empty()
			u = EXTRA-MIN(Q)
			S = S union {u}
			for each vertex v in G.adj[u]
				RELAX(u, v, w)
		 * */
		void dijkstra() {
			initilize();
			int start = 0;
			vector<int> parent(d_size, INT_MAX);
			vector<int> upper(d_size, INT_MAX); // u.d
			upper[start] = 0;
			vector<bool> inQ(d_size, true);
			multiset<pair<int, int>> fakeq; // use mutiset to simulate priority queue
			for (int i = 0; i < d_size; ++i) {
				fakeq.insert({upper[i], i});
			}
			vector<int> S; // result
			vector<int> dist(d_size, 0);
			while (!fakeq.empty()) {
				auto c = *fakeq.begin();
				fakeq.erase(fakeq.begin());
				int u = c.second;
				S.push_back(u);
				dist[u] = c.first;
				inQ[u] = false;
				for (auto&e : d_edges[u]) {
					int v = e.first;
					if (inQ[v]) {
						// releax
						int candidate = upper[u]; // == dist[u]
                        if (candidate != INT_MAX) {
                            candidate += e.second;
                        }
                        if ( candidate < upper[v]) {
							fakeq.erase(fakeq.find({upper[v], v}));
							upper[v] = candidate;
							fakeq.insert({upper[v], v});
						}
					}
				}
			}
			displayvector(S);
			displayvector(dist);
			displayvector(upper);
		}
	private:
		int d_size;
        vector<vector<pair<int, int>>> d_edges;
        void initilize(){
            d_size = 5;
			d_edges.clear();
			d_edges.resize(d_size);
			d_edges[0].push_back({1, 10});
			d_edges[0].push_back({4, 5});

			d_edges[1].push_back({2, 1});
			d_edges[1].push_back({4, 2});

			d_edges[2].push_back({3, 4});

			d_edges[3].push_back({2, 6});
			d_edges[3].push_back({0, 7});

			d_edges[4].push_back({1, 3});
			d_edges[4].push_back({2, 9});
			d_edges[4].push_back({3, 2});
        }
};

int main() {
	Solution s;
	s.dijkstra();
	return 0;
}
