#include "common.h"
class Solution {
public:
    //reference : https://www.cnblogs.com/grandyang/p/11186533.html
	int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
		// when you want to find min/max element, use priority_queue :)
		// according to current fuel, add all element within currentfuel range to fuelCandidates
		// pick the top one
		// if fuel is not enough, then pick the second largest of previous candidate, which is front of current q.
		int i = 0;
		int n = stations.size();
		int currentFuel = startFuel;
		int stops = 0;
		priority_queue<int> fuelCandidates;
		for (; currentFuel < target; stops++) {
			while (i < n && currentFuel >= stations[i][0]) {
				fuelCandidates.push(stations[i][1]);
				i++;
			}
			if (fuelCandidates.empty()) return -1;
			currentFuel += fuelCandidates.top();
			fuelCandidates.pop();
		}
		return stops;
	}
};

int main() {

	Solution s;

	return 0;
}
