#include "common.h"
class Solution {
public:
	bool checkSubarraySum(vector<int>& nums, int k) {
		if (nums.empty()) {
			return k == 0;
		}
		k = abs(k);
		if (k != 0) {
			for (auto&i : nums) {
				i %= k;
			}
		}

		int prefixSum = 0;
		unordered_map<int, int> cache;
		cache[0] = -1;
		for (size_t i = 0; i < nums.size(); ++i) {
			prefixSum += nums[i];
			if (k != 0) {
				prefixSum %= k;
			}
			if (cache.find(prefixSum) != cache.end()) {
				int preIndex = cache[prefixSum];
				if (i - preIndex >= 2) {
					return true;
				}
			}
			else {
				cache[prefixSum] = i;
			}
		}
		return false;
	}
};

int main() {

	Solution s;

	return 0;
}
