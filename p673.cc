#include "common.h"

class Solution {
public:

	int findNumberOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;
		int n = nums.size();
        vector<int> len(n, 1);   // the length of LIS ending at i
        vector<int> count(n, 1); // how many ways of geting LIS ending at i

        for (int i = 1; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				if (nums[i] > nums[j]) {
					// here LIS ending at j + nums[i] is candidate for i
					if (len[j] + 1 > len[i]) { // new solution is > than old solution, update
						len[i] = len[j] + 1;
                        // !!!
						count[i] = count[j]; // not count[j], there are only count[j] ways
					}
					else if (len[j] + 1 == len[i]) {
						// candidate's length == old LIS's length
						// add it
						count[i] += count[j];
					}
				}
			}
		}
		int maxLen = *max_element(len.begin(), len.end());
		int result = 0;
		for (int i = 0; i < n; ++i) {
			if (maxLen == len[i]) {
				result += count[i];
			}
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
