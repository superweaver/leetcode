#include "common.h"

class Solution {
  public:
    int findTargetSumWays(vector<int> &nums, int S) {
        /* idea: math
           sum(P) - sum(N) = targetSum;
           sum(P) = targetSum + sum(N);
           sum(P) + sum(P) = targetSum + sum(N) + sum(P)
           2*sum(P) = targetSum + totalSum
         */
        int sz = nums.size();
        int sum = 0;

        // Find sum
        for (int i = 0; i < sz; ++i) {
            sum += nums[i];
        }

        if (sum < S)
            return 0;

        // the (targetSum + totalSum) is required to be even before solution exists
        sum += S;
        if (sum & 0x1u)
            return 0;

        // Half the sum to find 2*sum(P)
        sum >>= 1;

        // init all dpSum to zero
        vector<int> dpSum(sum + 1, 0);
        //int dpSum[sum + 1] = {0}; // key !!!

        // if the difference is 0, you found a solution
        // sum(P) = (targetSum + totalSum)/2
        dpSum[0] = 1;
        for (int i = 0; i < sz; ++i) {
            // pay attention to order and boundary
            for (int eachSum = sum; eachSum >= nums[i]; eachSum--) {
                dpSum[eachSum] += dpSum[eachSum - nums[i]];
            }
        }
        return dpSum[sum];
    }
};

int main() {

    Solution s;

    return 0;
}
