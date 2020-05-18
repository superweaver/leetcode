#include "common.h"
class Solution {
public:
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
        vector<pair<int, int>> cache;
        int n = startTime.size();
        for (int i = 0; i < n; ++i) {
            cache.push_back({startTime[i], 1});
            cache.push_back({endTime[i] + 1, -1});
        }
        sort(cache.begin(), cache.end());
        if (queryTime < cache.front().first || queryTime >= cache.back().first) {
            return 0;
        }
        int count = 0;
        for (auto &p : cache) {
            if (p.first <= queryTime) {
                count += p.second;
            } else {
                return count;
            }
        }
        return count;
    }
};

int main() {

    vector<int> start = {4};
    vector<int> end = {4};
    int queryTime = 4;
	Solution s;

    cout << s.busyStudent(start, end, queryTime) << endl;

	return 0;
}
