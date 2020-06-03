#include "common.h"
class Solution {
public:
	int flipgame(vector<int>& fronts, vector<int>& backs) {
		// if fronts[i] == backs[i], there are not solution
		// the remaining min is the solution
        //
		//  1 <= fronts[i] <= 2000.
		//	1 <= backs[i] <= 2000.
		bitset<2001> same(0); // same in fronts and backs
		int n = fronts.size();
		for (int i = 0; i < n; ++i) {
			if (fronts[i] == backs[i]) {
				same.set(fronts[i], 1); // nice
			}
		}
		int result = INT_MAX;
		for (auto i : fronts) {
			if (i < result && !same.test(i)) {
				result = i;
			}
		}
		for (auto i : backs) {
			if (i < result && !same.test(i)) {
				result = i;
			}
		}
		return result == INT_MAX ? 0 : result;
	}
};

int main() {

	Solution s;

	return 0;
}
