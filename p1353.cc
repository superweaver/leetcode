#include "common.h"
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
		multiset<pair<int, int>> cache;
		for(auto &v :events) {
			cache.insert({v[0], v[1]});
		}
		int result = 0;
		int expect = cache.begin()->first;
        while (!cache.empty()) {
			if (expect > cache.begin()->second) {
				cache.erase(cache.begin());
				continue;
			} else {
                if (expect < cache.begin()->first) {
					expect = cache.begin()->first;
                } else if (expect > cache.begin()->first) {
                    pair<int, int> tmp{expect, cache.begin()->second };
                    cache.erase(cache.begin());
                    cache.insert(tmp);
                } else {
                    result++;
					expect++;
                    cache.erase(cache.begin());
                }
            }
        }
        return result;
    }
};

int main() {

	vector<vector<int>> events = {{1,2},{2,3},{3,4}}; // 3
	//events= {{1,2},{2,3},{3,4},{1,2}};//4
	//events = {{1,4},{4,4},{2,2},{3,4},{1,1}}; // 4
	//events = {{1,100000}}; // 1
	//events = {{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7}};// 7;
    events = { { 1, 2 }, { 1, 2 }, { 3, 3 }, { 1, 5 }, { 1, 5 } };// 5
	events = {{52,79},{7,34}};

    Solution s;
	cout << s.maxEvents(events) << endl;

	return 0;
}
