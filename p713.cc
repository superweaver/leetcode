#include "common.h"
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        /*
        */
        vector<int> dp(n, 0); // the longest length of subarray ending at i, whose contiguous product is less than k
        int p = 1;
        dp[0] = nums[0] < k ? 1 : 0;
        p = nums[0];
        for(int i = 1; i < n; ++i) {
            if (dp[i - 1] == 0) {
                dp[i] = nums[i] < k ? 1 : 0;
                p = nums[i];
            } else {
                if (nums[i] >= k) {
                    dp[i] = 0;
                    p = nums[i];
                } else {
                    if (p * nums[i] < k) {
                        dp[i] = dp[i - 1] + 1;
                        p *= nums[i];
                    } else {
                        int len = dp[i - 1];
                        while (len) {
                            p /= nums[i - len];
                            --len;
                            if (p * nums[i] < k) {
                                break;
                            }
                        }
                        dp[i] = len + 1;
                        p *= nums[i];
                    }
                }
            }
        }
        return accumulate(dp.begin(), dp.end(), 0);
    }
};


int main() {

	Solution s;

	return 0;
}
