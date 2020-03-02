#include "common.h"
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
		int m = mat.size();
		priority_queue<pair<int, int>> q;
		for (int i = 0; i < m; ++i) {
			auto &v = mat[i];
            int sum = distance(v.begin(), lower_bound(v.begin(), v.end(), 0, greater<int>()));
            if (q.size() < size_t(k)) {
				q.push({sum, i});
			} else {
				if (sum < q.top().first) {
					q.pop();
					q.push({sum, i});
				}
			}
		}
		vector<int> result(k, 0);
		while(!q.empty()) {
			result[--k] = q.top().second;
			q.pop();
		}
		return result;
    }
};

int main() {
    vector<vector<int>> mat = { { 1, 1, 0, 0, 0 },
                                { 1, 1, 1, 1, 0 },
                                { 1, 0, 0, 0, 0 },
                                { 1, 1, 0, 0, 0 },
                                { 1, 1, 1, 1, 1 } };
    int k = 3; // 2 0 3
    mat = { { 1, 0, 0, 0 }, { 1, 1, 1, 1 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 } }, k = 2;

    Solution s;
	displayvector(s.kWeakestRows(mat, k));

	return 0;
}
