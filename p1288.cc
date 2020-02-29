#include "common.h"
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
		int n = intervals.size();
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            } else {
                return a[1] > b[1];
            }
        });
        int remove = 0;
		int pre_cover = -1;
		for (auto &v : intervals) {
			if (v[1] <= pre_cover) {
                remove++;
            } else {
				pre_cover = v[1];
			}
		}
		return n - remove;
    }
};

int main() {
	vector<vector<int>> intervals = {{1,4},{3,6},{2,8}};
	Solution s;
	cout << s.removeCoveredIntervals(intervals) << endl;

	return 0;
}
