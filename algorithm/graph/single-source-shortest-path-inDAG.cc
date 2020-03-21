#include "../../../common.h"
class Solution {
public:
    void initialize()
    {
		d_edges.clear();
        d_size = 6;
		d_edges.resize(d_size);
		d_edges[0].push_back({1, 5});
		d_edges[0].push_back({2, 3});

		d_edges[1].push_back({2, 2});
		d_edges[1].push_back({3, 6});

		d_edges[2].push_back({3, 7});
		d_edges[2].push_back({4, 4});
		d_edges[2].push_back({5, 2});

		d_edges[3].push_back({4, -1});
		d_edges[3].push_back({5, 1});

		d_edges[4].push_back({5, -2});
    }
	void shortestpathinDAG() {
		initialize();
        int start = 1; // !!! Figure 24.5
        vector<int> parent(d_size, INT_MAX);
        vector<int> upper(d_size, INT_MAX);
        upper[start] = 0;

        vector<int> color(d_size, 0); // white
		vector<int> reversedorder;
		for (int i = 0; i < d_size; ++i) {
			if (color[i] == 0) {
				dfs(i,color, reversedorder);
			}
		}

        for (int i = reversedorder.size() - 1; i >= 0; --i) {
            // do relaxation
			int u = reversedorder[i];
			for(auto& e : d_edges[u]) {
				int v = e.first;
				int candidate = upper[u];
				if (candidate != INT_MAX) {
					candidate += e.second;
				}
				if (upper[v] > candidate) {
					upper[v] = candidate;
					parent[v] = u;
				}
			}
        }
		displayvector(parent);
		displayvector(upper);
    }

private:
    int d_size;
    vector<vector<pair<int, int>>> d_edges;
    void dfs(int start, vector<int>& color, vector<int>& reversedorder) {
		color[start] = 1;
		for (auto& e : d_edges[start]) {
			if (color[e.first] == 0) {
				dfs(e.first, color, reversedorder);
			}
		}
		reversedorder.push_back(start);
		color[start] = 2;
	}
};
int main() {
	Solution s;
	s.shortestpathinDAG();
	return 0;
}
