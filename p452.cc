#include "common.h"
// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/discuss/93735/A-Concise-Template-for-%22Overlapping-Interval-Problem%22
class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        int n = points.size();
        if (0 == n) {
            return 0;
        }
        sort(points.begin(), points.end());
        vector<pair<int, int>> q;
        q.push_back(points[0]);
        int i = 1;
        while (i < n) {
            if (q.back().second >= points[i].first) {
                q.back().first = max(points[i].first, q.back().first);
                q.back().second = min(points[i].second, q.back().second);
            } else {
                q.push_back(points[i]);
            }
            i++;
        }
        //for (auto p : q) {
        //    cout << p.first << ":" << p.second << endl;
        //}

        return q.size();
    }
};


int main() {

	Solution s;

	return 0;
}
