#include "common.h"
// a good template
class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		unordered_map<int, int> cumulative_sums;// prefix_sum : the times of prefix_sum have appeared
		int result = 0;
		int cumulative_sum = 0;
		cumulative_sums[0] = 1; // prefix_sum at -1 is zero
		for (int i = 0; i < (int)nums.size(); i++) {
			cumulative_sum += nums[i];
			if (cumulative_sums.find(cumulative_sum - k) != cumulative_sums.end()) {
				// it is sure that the indices corresponding to cumulative_sums[cumulative_sum - k] are all less than i
				// and we are checking index i; so it is safe to add cumulative_sums[cumulative_sum - k]
				result += cumulative_sums[cumulative_sum - k]; //!!!
			}
			cumulative_sums[cumulative_sum]++;
		}
		return result;

	}
};

int main() {

	Solution s;

	return 0;
}
