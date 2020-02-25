#include "common.h"
class Solution {
public:
    int minCostToMoveChips(vector<int>& chips) {
        int n = chips.size();
        int odd = 0;
		// place even positions in on group
		// place odd positions in another group
		// move the smaller of these two groups to the other at the cost of the size of smaller group
        for (auto i : chips){
            odd += (i & 1);
        }
        return min(odd, n - odd);
    }
};

int main() {

	Solution s;

	return 0;
}
