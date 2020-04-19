#include "common.h"
class Solution
{
public:
	int minStartValue(vector<int>& nums)
	{
		int n = nums.size();
		//vector<int> prefix_sum(n + 1, 0);
		int prefix_sum = 0;
		int min_sum = INT_MAX;
		for(int i = 0; i < n; ++i)
		{
			//	prefix_sum[i + 1] = prefix_sum[i] + nums[i];
			prefix_sum += nums[i];
			//min_sum = min(min_sum, prefix_sum[i + 1]);
			min_sum = min(min_sum, prefix_sum);
		}

		if(min_sum >= 1)
		{
			return 1;
		}
		else
		{
			return 1 - min_sum;
		}
	}
};

int main()
{

    vector<int> nums{-3,2,-3,4,2}; // 5
    nums = {1, 2}; // 1
    nums = {1, -2, -3};
	Solution s;
    cout << s.minStartValue(nums) << endl;
	return 0;
}
