#include "common.h"
//https://leetcode.com/problems/set-intersection-size-at-least-two/discuss/113089/C++-concise-solution-O(nlogn)-greedy-39-ms
class Solution {
  public:
    int intersectionSizeTwo2(vector<vector<int>> &intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] > b[0]);
        });
        vector<int> r = {-1, -1};
        for (auto &v : intervals) {
            if (v[0] > r.back()) {
                // no overlap
                // add both v[1]-1 and v[1] to r
                r.push_back(v[1] - 1);
                r.push_back(v[1]);
            } else if (v[0] > r[r.size() - 2]) {
                // has only overlap at r.back();
                // add v[1] to r
                r.push_back(v[1]);
            } else {
                // do nothing
                // have >= 2 overlaps
            }
        }
        return r.size() - 2;
    }

    int intersectionSizeTwo(vector<vector<int>> &intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[1] < b[1] || (a[1] == b[1] &&
                                   a[0] > b[0]); // !!!bigger a[0] is ahead to minimize the size of set
        });
        int p = -1; // the max in the set
        int q = -1; // the second max in the set
        int ans = 0; // size of set
        for (auto &v : intervals) {
            if (v[0] > p) {
                // v has no overlap with current set
                // add both v[1]-1 and v[1] to set
                // update p and q
                p = v[1];
                q = v[1] - 1; // !!! not the v[0]
                ans += 2;
            } else if (v[0] > q) {
                // v[0] <= p && v[0] > q
                // v[1] > v[0]
                // has only overlap at the max of set
                // add v[1] to r && v[0] <= p, in this way, at least 2 elements can be covered
                // can't cover v[0]
                // but p is covered in interval
                // so keep p and add v[1] as new max
                q = p;
                p = v[1];
                ans += 1;
            } else {
                // do nothing
                // have >= 2 overlaps
            }
        }
        return ans;
    }
};

int main() {

	Solution s;

	return 0;
}
