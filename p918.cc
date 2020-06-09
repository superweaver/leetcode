#include "common.h"

class Solution {
public:
	// https://www.cnblogs.com/grandyang/p/11716314.html
	int maxSubarraySumCircular(vector<int>& A) {
		int sum = 0;
		int min_sum = INT_MAX; // assume not a circular array
		int max_sum = INT_MIN;
		int max_sum_end_at_i = 0;
		int min_sum_end_at_i = 0;
		for (auto i : A) {
			max_sum_end_at_i = max(max_sum_end_at_i + i, i);
			max_sum = max(max_sum, max_sum_end_at_i);
			min_sum_end_at_i = min(min_sum_end_at_i + i, i);
			min_sum = min(min_sum, min_sum_end_at_i);
			sum += i;
		}
        // 1) max_sum, min_sum
        // 2) all negative !!!
        //
		// when all elements in A are negative, sum == min_sum, sum - min_sum = 0 > max_sum;
		return sum == min_sum ? max_sum : max(max_sum, sum - min_sum); // tricky
	}
};

int main() {

	Solution s;

	return 0;
}
