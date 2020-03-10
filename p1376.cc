#include "common.h"
class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
		unordered_map<int, vector<int>> children;
		for (int i = 0; i < n ; ++i) {
			if (i == headID) {
				continue;
			}
			children[manager[i]].push_back(i);
		}
		return helper(headID, children, informTime);
	}
	int helper(int root, unordered_map<int, vector<int>>& children, vector<int>& informTime) {
		if (!children.count(root)) {
			return 0;
		}
		int r = 0;
		auto&v = children[root];
		for (auto c : v) {
			r = max(r, helper(c, children, informTime));
		}
		return r + informTime[root];
	}

    int numOfMinutes2(int n, int headID, vector<int>& manager, vector<int>& informTime) {
		// find leaves
		vector<bool> isleaves(n, true);
		for(int i = 0; i < n; ++i) {
			if (manager[i] >= 0) {
				isleaves[manager[i]] = false;
			}
		}
        unordered_map<int, int> level;
        for (int i = 0; i < n; ++i) {
			if(isleaves[i]) {
				level[i] = 0;
			}
        }

        while (!(level.size() == 1 && level.begin()->first == -1)) {
            unordered_map<int, int> upper;
            for (auto& p : level) {
                int m = p.first >= 0 ? manager[p.first] : -1;
                int t = p.second + (m >= 0 ? informTime[m] : 0);
                upper[m] = max(upper[m], t);
            }
            upper.swap(level);
        }

        return level.begin()->second;
    }
};

int main() {
    int n = 7;
	int headID = 6;
    vector<int> manager = { 1, 2, 3, 4, 5, 6, -1 };
    vector<int> informTime = { 0, 6, 5, 4, 3, 2, 1 };
    n = 4, headID = 2, manager = { 3, 3, -1, 2 }, informTime = { 0, 0, 162, 914 };  // 1076
    n = 15, headID = 0, manager = { -1, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6 },
    informTime = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };  // 3
    n = 1, headID = 0, manager = { -1 }, informTime = { 0 };
//	n = 6, headID = 2, manager = {2,2,-1,2,2,2}, informTime = {0,0,1,0,0,0};
//	n = 8, headID = 0,manager = {-1,5,0,6,7,0,0,0}, informTime = {89,0,0,0,0,523,241,519};

    Solution s;
	cout << s.numOfMinutes(n, headID, manager, informTime) << endl;
    return 0;
}
