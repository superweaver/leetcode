#include "common.h"
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums)
    {
        int total = accumulate(nums.begin(), nums.end(), 0);
		sort(nums.begin(), nums.end(), greater<int>());
		int sum = 0;
        size_t end = nums.size();
        for(size_t i = 0; i < nums.size(); ++i) {
			if (sum <= total - sum) {
				sum += nums[i];
			} else {
				end = i;
				break;
			}
		}
        return { nums.begin(), nums.begin() + end };
    }
};

int main()
{
    vector<int> nums{ 4, 3, 10, 9, 8 };  // 10, 9
    nums = { 4, 4, 7, 6, 7 };            // 7 , 7 , 6
     nums = { 6 };
	//nums = {3, 5};

    Solution s;
    displayvector(s.minSubsequence(nums));

    return 0;
}
