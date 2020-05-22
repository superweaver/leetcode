#include "common.h"
// not solved
// http://www.cnblogs.com/grandyang/p/6017505.html
class Solution {
public:
    int eraseOverlapIntervals(vector<Interval>& intervals) {
		if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(),
             [](Interval &a, Interval &b) { return a.start < b.start; });
        int last = 0; // index of right most interval in currently non-overlaping intervals
                      // interval[last] has the largest end
		int result = 0;
		int n = intervals.size();
		for (int i = 1; i < n; ++i) {
			if (intervals[last].end > intervals[i].start) {
				//overlap with last non overlapping interval
				++result;
				if (intervals[i].end < intervals[last].end) {
					last = i;
				}
                // else last is not changed.
			}
			else { // no overlapping
				last = i;
			}
		}
		return result;
    }
};

int main() {

	Solution s;

	return 0;
}
