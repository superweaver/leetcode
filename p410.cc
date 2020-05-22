#include "common.h"
// not solved
//https://blog.csdn.net/cc_fys/article/details/80614373
//https://blog.csdn.net/MebiuW/article/details/52724293
//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-410-split-array-largest-sum/

// binary search
class Solution {
public:
    int splitArray(vector<int>& nums, int m)
    {
        int maxv = INT_MIN;
        long sum = 0;
        for (auto num : nums) {
            sum += num;
            maxv = max(maxv, num);
        }
        return binarysearch(nums, m, maxv, sum);
    }

private:
    int binarysearch(vector<int>& nums, int m, int low, long high)
    {
        while (low < high) {
            int mid = low + (high - low) / 2;
            // check if there are more than m divisions whose max sum is <= mid;
            int count = 1;  // the number of divisions whose sum is as large as possible but <= mid
            int sum = 0;
            for (auto num : nums) {
                sum += num;
                if (sum > mid) {
                    count++;
                    sum = num;  // key
                    if (count > m) {
                        break;
                    }
                }
            }
            if (count <= m) {
                // mid is too small
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};

// not solved
//https://blog.csdn.net/cc_fys/article/details/80614373
//https://blog.csdn.net/MebiuW/article/details/52724293
//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-410-split-array-largest-sum/

// dp
class Solution_dp {
public:
    int splitArray(vector<int>& nums, int m)
    {
        // dp
        // dp[i][j] is the min of max sum of each group in a total of i groups by dividing j elements
        // dp[0][0] = 0;
        // dp[i][0] = 0;
        // dp [1][j] = sum of nums[0, j)
        // note: j >= i  !!!
        // generally, we have dp[i][j] = min(dp[i][j], max(dp[i-1][k] , sum of nums[k, j))) for any i-1 <= k < j
        // return dp[m][n]
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + nums[i];
        }
        // sum[i] = sum of nums[0, i)
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, INT_MAX));
        for (int j = 1; j <= n; ++j) {
            dp[1][j] = sum[j];
        }
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = 0;
        }
        for (int i = 2; i <= m; ++i) {
            for (int j = i; j <= n; ++j) {
                for (int k = i - 1; k < j; ++k) {
                    // for (int k = 0; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], max(dp[i - 1][k], sum[j] - sum[k]));
                }
            }
        }
        return dp[m][n];
    }
};




int main() {

	Solution s;

	return 0;
}
