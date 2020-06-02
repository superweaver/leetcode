#include "common.h"

class Solution {
public:
	// https://www.cnblogs.com/grandyang/p/9286537.html
	// dp[i][j] is the amount of wine poured upon layer i glass cup j
	// dp[0][0] is poured
	// if dp[i][j] > 1, then split the overflow into next layer
	double champagneTower(int poured, int query_row, int query_glass) {
		vector<double> current;
		vector<double> next;
		int i = 0;
		current.resize(i + 1);
		current[0] = poured;
		while (i < 101) {
			next = vector<double>(i + 2, 0);
			for (int j = i; j >= 0; --j) {
				if (current[j] > 1) {
					double overflow = (current[j] - 1) / 2.0;
					next[j + 1] += overflow;
					next[j] += overflow;
					current[j] = 1;
				}
			}
			if (i == query_row) {
				return current[query_glass];
			}
			current.swap(next);
			++i;
		}
        return 0;
		//return DBL_MIN;
	}
};

int main() {

	Solution s;

	return 0;
}
