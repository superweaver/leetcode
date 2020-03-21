#include "../../../common.h"
class Solution {
public:
    void initialize()
    {
		edges.clear();
        edges.push_back({ 0, 1, 6 });
        edges.push_back({ 0, 4, 7 });
        edges.push_back({ 1, 2, 5 });
        edges.push_back({ 1, 3, -4 });
        edges.push_back({ 1, 4, 8 });
        edges.push_back({ 2, 1, -2 });
        edges.push_back({ 3, 2, 7 });
        edges.push_back({ 3, 0, 2 });
        edges.push_back({ 4, 2, -3 });
        edges.push_back({ 4, 3, 9 });
		d_size = 5;
    }
    bool bellman_ford()
    {
        /*
  BELLMAN -FORD(G, w, s)
 INITIALIZE-SINGLE-SOURCE(G, s)
 for i = 1 to |G.V| - 1
    for each edge .u;
        RELAX(u, v, w);
  for each edge (u,v)
     if (v.d > u.d + w(u, v))
        return false
    return true;
  */
		initialize();
        vector<int> order;
        vector<int> dist;
        int start = 0;
        vector<int> parent(d_size, INT_MAX);
        vector<int> upper(d_size, INT_MAX);  // v.d
        upper[start] = 0;
		for (int i = 0; i < d_size - 1; ++i) {
			for (auto &e : edges) {
				int u = e[0];
				int v = e[1];
				int w = e[2];
                int candidate = upper[u];
                if (upper[u] != INT_MAX) {
                    candidate = upper[u] + w;
                }
                if (upper[v] > candidate) {
					upper[v] = candidate;
					parent[v] = u;
				}
			}
        }
		vector<int> result;
		vector<int>child(d_size, INT_MIN);
		for (int i = 0; i < d_size; ++i) {
			if (parent[i] == INT_MAX) {
				continue;
			} else {
				child[parent[i]] = i;
			}
		}
		displayvector(parent);
		displayvector(upper);
		for (auto&e : edges) {
			if (upper[e[1]] > upper[e[0]] + e[2]) {
                cout << "there is a negative cycle" << endl;
				return false;
            }
		}
		
        return true;
    }

private:
	//vector<vector<pair<int, int>>> edges;
	vector<vector<int>> edges;
	int d_size;
    
};
int main() {
	Solution s;
	s.bellman_ford();
	return 0;
}
