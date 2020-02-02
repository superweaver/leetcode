#include "common.h"
class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
		// Union-Find
		int N = grid.size();
		int len = (N*N) << 2;
		// divide each grid into four sub grid
		// North, East, South, West -> 0, 1, 2, 3
		vector<int> dirs = {-1, 0, 1, 0, -1};
		DJS uf(len);
		for (int r = 0; r < N; ++r) {
			for (int c = 0; c < N; ++c) {
				int base = (r * N + c) << 2;
				if (grid[r][c] == ' ') {
					for (int i = 0; i < 3; ++i) {
						uf.Union(base +i, base + i + 1);
					}
				} else {
					if (grid[r][c] == '/') {
						uf.Union(base + 0 , base + 3);
						uf.Union(base + 1, base + 2);
					} else {
						uf.Union(base + 0 , base + 1);
						uf.Union(base + 2, base + 3);
					}
				}
				// care top and left only
				if (c > 0) {
					int base_left = base - 4;
					uf.Union(base_left + 1, base + 3);
				}
				if (r > 0) {
					int base_up = base - N * 4;
					uf.Union(base_up + 2, base + 0);
				}
			}
		}
		// while(len) { uf.Find(len--); }
		return uf.getGroups();
    }
private:
	struct DJS {
		DJS(int n) {
			groups = n;
			sizes = vector<int>(n, 1);
			for(int i = 0; i < n; ++i) {
				parents.push_back(i);
			}
		}
		int getGroups() {
			return groups;
		}
		int Find(int node) {
			while (node != parents[node]) {
				parents[node] = parents[parents[node]];
				node = parents[node];
			}
			return node;
		}
		void Union(int u , int v) {
			int uid = Find(u);
			int vid = Find(v);
			if (uid == vid) return;
			int& usize = sizes[uid];
			int& vsize = sizes[vid];
			groups--;
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
			int groups;
	};
};

int main() {

	vector<string> grid = { " /", "/ " }; // 2
	//grid =	{ " /", "  " }; // 1
	//grid = {  "\\/", "/\\"}; // 4
	//grid = { "/\\", "\\/"}; // 5
	//grid = {"//", "/ "}; // 3
	Solution s;
	cout << s.regionsBySlashes(grid) << endl;
	return 0;
}
