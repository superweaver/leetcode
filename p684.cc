#include "common.h"

class Solution {
public:
	vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		// https://www.youtube.com/watch?v=4hJ721ce010
		// union-find
		if (edges.empty()) return {};
		int N = edges.size();
		vector<int> groupID(N + 1, 0); // 0 is not used;
		for (int i = 0; i <= N; ++i) {
			groupID[i] = i;
		}
		vector<int> groupSize(N + 1, 1);
		for (auto& e : edges) {
			int u = e[0];
			int v = e[1];
			int uid = findGroupID(u, groupID);
			int vid = findGroupID(v, groupID);
			if (uid == vid) {
				return e;
			} else {
                // union uid and vid (two groups)
			    unionGroup(uid, vid, groupSize, groupID);
            }
		}
		return {};
	}
private:
		int findGroupID(int u, vector<int>& groupID) {
		while (u != groupID[u]) {
			groupID[u] = groupID[groupID[u]]; // grand parent
			u = groupID[u];
		}
		return u;
	}
	void unionGroup(int uid, int vid, vector<int>& groupSize, vector<int>& groupID) {
		if (groupSize[uid] < groupSize[vid]) {
			swap(uid, vid);
		}
		// attach smaller to larger tree
		groupID[vid] = uid;
		groupSize[uid] += groupSize[vid];
		// groupSize[vid] is unchanged
	}
};

int main() {

	Solution s;

	return 0;
}
