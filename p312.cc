#include "common.h"
class Solution {
  public:
    // http://www.cnblogs.com/grandyang/p/5006441.html
    // https://blog.csdn.net/Zarlove/article/details/76577460
    int maxCoins(vector<int> &nums) {
        // dp[i][j] is the max coins we can get by bursting all balloons from i to j
        // note: after bursting all ballons from i to j, for ballons on the right of j, what they
        // can see is nums[i-1] for ballons on the left of i, what they can see is nums[j+1] !!!!
        // the dp[i][j] = max{dp[i][j], dp[i][k-1] + dp [k+1][j] + nums[i-1]*nums[k]*nums[j+1]} for
        // i <= k <= j add two ones on the left and right of nums
        int oldSize = nums.size();
        vector<int> input(2 + oldSize, 1);
        for (int i = 0; i < oldSize; ++i) {
            input[i + 1] = nums[i];
        }
        int newSize = input.size();
        vector<vector<int>> dp(newSize, vector<int>(newSize, 0));
        for (int len = 1; len <= oldSize; ++len) {         // j - i + 1 = len
            for (int i = 1; i + len + 1 <= newSize; ++i) { // 1 <= i <= newSize - 1 - len
                int j = i + len - 1;
                for (int k = i; k <= j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k - 1] + dp[k + 1][j] +
                                                 input[i - 1] * input[k] * input[j + 1]);
                }
            }
        }
        return dp[1][oldSize];
    }
};

int main() {

	Solution s;

	return 0;
}
