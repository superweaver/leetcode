#include "common.h"
class UF {
	public:
	UF(int n) {
		groups = n;
		sizes = vector<int>(n, 1);
		parent = vector<int>(n, 0);
		extra = 0;
        for (int i = 0; i < n; ++i) {
			parent[i] = i;
        }
    }
	int Find(int node) {
		while(node != parent[node]) {
			parent[node] = parent[parent[node]];
			node = parent[node];
		}
		return node;
	}
	void Union(int u, int v) {
		int uid = Find(u);
		int vid = Find(v);
        if (uid == vid) {
			extra++;
            return;
		}
		groups--;
		int& usize= sizes[uid];
		int& vsize = sizes[vid];
		//if ((usize&0xFFFF) < (vsize&0xFFFF)) {
		// extra can also be stroed at upper 16 bits of sizes
		if (usize < vsize) {
			vsize += usize;
			parent[uid] = vid;
		} else {
			usize += vsize;
			parent[vid] = uid;
		}
    }

public:
    vector<int> sizes;
	vector<int> parent;
	int groups;
	int extra;
};
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
		int c_size = connections.size();
		if (c_size < n -1) {
			return -1;
		}
		UF uf(n);
		for(auto&v : connections) {
			uf.Union(v[0], v[1]);
		}
		if (uf.extra < uf.groups - 1) {
			return -1;
		}
        return uf.groups - 1;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> connections = { { 0, 1 }, { 0, 2 }, { 1, 2 } }; // 1
	n = 6, connections = {{0,1},{0,2},{0,3},{1,2},{1,3}}; // 2
	n = 6, connections = {{0,1},{0,2},{0,3},{1,2}}; // -1
	n = 5, connections = {{0,1},{0,2},{3,4},{2,3}}; // 0




    Solution s;
	cout << s.makeConnected(n, connections) << endl;

    return 0;
}
