#include "common.h"
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		 // O(n*log(n))
		int n = nums.size();
		if(!n)
		{
			return 0;
		}

        // keep a monotonic increasing sequence, !!!
        vector<int> dp;
        for (int i = 0; i < n; ++i) {
            auto it = lower_bound(dp.begin(), dp.end(), nums[i]);
			if(it != dp.end())
			{
				 // good to replace previous element
                 // why? length of LIS is not impact, but the end value is lowered or unchanged
                *it = nums[i];
			}
			else
			{
				dp.push_back(nums[i]);
			}
		}
		return dp.size(); // only size is useful

	}
};

int main() {

	Solution s;

	return 0;
}
