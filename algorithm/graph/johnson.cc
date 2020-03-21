#include "../../../common.h"
/*
 * JOHNSON(G, w)
	compute G’, where G’.V = G.V union {s}
		G’.E = G.E union {(s, v), v in  G.V}
		and w(s, v) = 0 for all v in G.V

	if BELLMAN-FORD(G’, w, s) == FALSE
		print "the input graph contains a negative-weight cycle"
	else for each vectex v in G’.V
		set h(v) to the value of δ(s,v) computed by the Bellman-Ford algorithm
		for each edge (u, v) in G’.E
			w_hat(u,v) = w(u,v) + h(u) – h(v)
		let D = (duv) be a new n by n matrix
		for each vertex u in G.V
			run DIJKSTRA(G, w_hat, u) to compute δ_hat(u,v) for all v in G.V
			for each vertex v in G.V
				duv = δ_hat(u,v) + h(v) – h(u)
	return D.
 */
class Solution {
public:
    Solution() {
		initilize();
	}
	void johnson() {
		d_size++;
		d_edges.push_back({}); // G'
		for (int i = 0; i < d_size - 1; ++i) {
			d_edges.back().push_back({i, 0});
		}
		vector<int> dGprime; // v.d in Gprime
		auto r = bellman_ford(d_edges, d_size-1, dGprime);
		if (!r) {
			cout <<  "the input graph contains a negative-weight cycle" << endl;
            return;
        }
		displayvector(dGprime);
		// dGprime is h vector
		const auto&h = dGprime;
		// change w to w_hat
		for (int u = 0; u < d_size; ++u) {
			for(auto& e : d_edges[u]) {
				int&v = e.first;
				int&w = e.second;
				w += h[u] - h[v];
			}
		}
		for (int i = 0; i < d_size; ++i) {
			for(auto &p : d_edges[i]) {
				cout << i << ":" << p.first << " = " << p.second << endl;
			}
		}
        vector<vector<int>> dG(d_size - 1, vector<int>(d_size - 1, INT_MAX));
		for (int u = 0; u < d_size - 1; ++u) {
			vector<int> duv_prime;
			dijkstra(d_edges, u, duv_prime); // duv_prime len == d_size
			for (int v = 0; v < d_size - 1; ++v) {
				dG[u][v] = duv_prime[v] + h[v] - h[u];
			}
		}
		for(auto&v: dG) {
			displayvector(v);
		}
    }
private:
	int d_size;
	vector<vector<pair<int, int>>> d_edges;
    void initilize() {
		d_size = 5;
        d_edges = vector<vector<pair<int, int>>>(d_size);
		d_edges[0].push_back({1, 3});
		d_edges[0].push_back({2, 8});
		d_edges[0].push_back({4, -4});

		d_edges[1].push_back({3, 1});
		d_edges[1].push_back({4, 7});

		d_edges[2].push_back({1, 4});

		d_edges[3].push_back({2, -5});
		d_edges[3].push_back({0, 2});

		d_edges[4].push_back({3, 6});
    }
    bool bellman_ford(vector<vector<pair<int, int>>> edges, int start, vector<int>& dGprime)
    {
		int n = edges.size();
		dGprime = vector<int>(n, INT_MAX); // v.d
		dGprime[start] = 0;

        for (int i = 0; i < n - 1; ++i) {
			for (int u = 0; u < n; ++u) {
				for(auto&e : edges[u]) {
					int v = e.first;
					int w = e.second;
					// relax
					int candidate =  dGprime[u];
					if (candidate != INT_MAX) {
						candidate += w;
					}
					if (dGprime[v] >  candidate) {
						dGprime[v] = candidate;
					}
				}
			}
        }
        for (int u = 0; u < n; ++u) {
            for (auto& e : edges[u]) {
                int v = e.first;
                int w = e.second;
                int candidate = dGprime[u];
				if (candidate != INT_MAX) {
					candidate += w;
				}
                //if (dGprime[v] > dGprime[u] + w) {
                if (dGprime[v] > candidate) {
					return false;
				}
            }
        }
        return true;
    }

    void dijkstra(vector<vector<pair<int, int>>>& edges, int start, vector<int>& duv_prime)
    {
        int n = edges.size();
        duv_prime = vector<int>(n, 0);
		vector<int> upper(n, INT_MAX);
		multiset<pair<int, int>> q;
		for (int i = 0; i < n; ++i) {
			if (i == start) {
				q.insert({0, start});
			} else {
				q.insert({INT_MAX, i});
			}
		}
		vector<bool> inQ(n, true);
		inQ[start] = false;
		while(!q.empty()) {
			auto c = *q.begin();
			q.erase(q.begin());
			int u = c.second;
			int w = c.first;
			inQ[u] = false;
			duv_prime[u] = w;
			for (auto&e : edges[u]) {
				int v = e.first;
				int weight = e.second;
				if (inQ[v]) {
					pair<int, int> node(upper[v], v);	
					//int candidate = upper[u]; // == w
					int candidate = w; // == w
					if (candidate != INT_MAX) {
						candidate += weight;
					}
					if (candidate < upper[v]) {
                        upper[v] = candidate;
                        q.erase(q.find(node));
						node.first = upper[v];
						q.insert(node);
					}
				}
			}
		}
    }
};
int main() {
	Solution s;
	s.johnson();
	return 0;
}
