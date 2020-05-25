#include "common.h"
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        if (nums.empty()) return true;
        // sum(i, j) = the sum of nums[i..j]  i <= j
        // dp(i, j) is the max value the choosing player can get when nums[i..j] are left
        // dp(i, j) = max(a, b);
        // a = nums[i] + sum(i+1, j) - dp(i+1, j);
        // b = nums[j] + sum(i, j-1) - dp(i, j-1);
        // dp[i][i] = nums[i];
        // return 2 * dp(0, n-1) >= sum(0, n-1)
        int n = nums.size();
        // we can use prefix_sum to get this
        vector<vector<int> > summation(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            int s = 0;
            for (int j = i; j < n; ++j) {
                s += nums[j];
                summation[i][j] = s;
            }
        }
        vector<vector<int> > dp(n, vector<int>(n, 0));
        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = nums[i];
        }
        for (int k = 1; k < n; ++k) {
            for (int i = 0; i < n - k; ++i) {
                int j = i + k;
                int a = nums[i] + summation[i + 1][j] - dp[i + 1][j];
                int b = nums[j] + summation[i][j - 1] - dp[i][j - 1];
                dp[i][j] = max(a, b);
                //cout << i << ", " << j << endl;
            }
        }
        return 2 * dp[0][n-1] >= summation[0][n-1];
    }
};

int main() {

	Solution s;

	return 0;
}
