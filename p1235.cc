#include "common.h"
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
		vector<pair<int,int>> endpoints;
		int n = startTime.size();
		for (int i = 0; i < n; ++i) {
			endpoints.push_back({startTime[i], i});
			endpoints.push_back({endTime[i], -profit[i]});
		}
		sort(endpoints.begin(), endpoints.end());
		unordered_map<int, int> cache;
		int r = 0;
		for (auto &p : endpoints) {
			if (p.second >= 0) {
				// update
                int end = endTime[p.second];
                cache[end] = max(cache[end], r + profit[p.second]);
			} else {
				r = max(r, cache[p.first]);
			}
		}
		return r;
    }
};

int main() {

    vector<int> startTime = { 1, 2, 3, 3 }, endTime = { 3, 4, 5, 6 }, profit = { 50, 10, 40, 70 }; // 120
	startTime = {1,2,3,4,6}, endTime = {3,5,10,6,9}, profit = {20,20,100,70,60}; // 150
	startTime = {1,1,1}, endTime = {2,3,4}, profit = {5,6,4};


    Solution s;
	cout << s.jobScheduling(startTime, endTime, profit) << endl;
	return 0;
}
