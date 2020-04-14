#include "common.h"
class Solution
{
public:
	// reference https://www.cnblogs.com/seyjs/p/11866017.html
	// https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1187-make-array-strictly-increasing/
	int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2)
	{
		constexpr int Inf = 1000000000; // no solution

		int m = arr1.size();
		sort(arr2.begin(), arr2.end());
		arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());
		int n = arr2.size();

		// keep[i] is the min steps to make arr1[0, i] valid while keep arr1[i] unchanged.
		vector<int> keep(m, Inf);
		keep[0] = 0; // no cost for first

		// dp[i][j] is the min steps to make arr1[0, i]
		// valid by assigning arr1[i] = arr2[j]
		vector<vector<int>> dp(m, vector<int>(n, Inf));
		dp[0].assign(n, 1); // dp[0][*] = 1

		// case 1: both arr1[i-1] and arr1[i] are not assigned, then it implies that
		// arr1[i] > arr1[i-1], at this time, keep[i] = keep[i-1]
		//
		// case 2 : only arr1[i] is assigned, then for any arr2[j] > arr1[i-1]
		// we have dp[i][j] = keep[i-1] + 1
		//
		// case 3: only arr1[i-1] is assigned, then for any arr2[j] < arr1[i]
		// we have keep[i] = dp[i-1][j] + 1
		//
		// case 4 : both arr1[i-1] and arr1[i] are assigned
		// if dp[i-1][j-1] is valid then dp[i][j] is valid by assigning i and j
		// dp[i][j] = dp[i-1][j-1] + 1

		for(int i = 1; i < m; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				// case 2 : only arr1[i] is assigned
				if(arr2[j] > arr1[i - 1])
				{
					dp[i][j] = min(dp[i][j], keep[i - 1] + 1);
				}
				// case 4 : both arr1[i] and arr1[i-1] are assigned
				if(j > 0)
				{
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
				}
				// case 3: only arr1[i-1] is assigned
				if(arr2[j] < arr1[i])
				{
					keep[i] = min(keep[i], dp[i - 1][j]);
				}
			}
			// case 1: none of arr1[i] and arr1[i-1] are assigned
			if(arr1[i] > arr1[i - 1])
			{
				keep[i] = min(keep[i], keep[i - 1]);
			}
		}
		const auto& dp_last = dp.back();
		auto r = min(keep.back(), *min_element(dp_last.begin(), dp_last.end()));
		return r == Inf ? -1 : r;
	}
};

int main()
{
	vector<int> arr1 = {1, 5, 3, 6, 7}, arr2 = {1, 3, 2, 4}; // 1
	//arr1 = {1, 5, 3, 6, 7}, arr2 = {4, 3, 1}; // 2
	//arr1 = {1, 5, 3, 6, 7}, arr2 = {1, 6, 3, 3}; // -1

	Solution s;
	cout << s.makeArrayIncreasing(arr1, arr2) << endl;

	return 0;
}
