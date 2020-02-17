#include "common.h"
class Solution {
public:
    int stoneGameII(vector<int>& piles)
    {
        int n = piles.size();
        int upperM = 2 * n + 1;
        vector<int> suffix_sum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffix_sum[i] = suffix_sum[i + 1] + piles[i];
        }
		// turn, start index, M
        // vector<vector<vector<int>>> dp(2, vector<vector<int>>(n, vector<int>(upperM, 0)));
		// turn is 0 for alex, 1 is for lee
		// turn is no needed
        vector<vector<int>> dp(n, vector<int>(upperM, 0));
        return helper(0, 1, piles, dp, suffix_sum);
    }

private:
    int helper(int start, int M, vector<int>& piles, vector<vector<int>>& dp,
               vector<int>& suffix_sum)
    {
        int leftstones = piles.size() - start;  // how many stones left
        if (leftstones <= 0) {
            return 0;
        }
        if (dp[start][M] > 0) {
            return dp[start][M];
        }
        int sum = 0;
        int upper = min(leftstones, 2 * M);
        int result = 0;
        for (int i = 1; i <= upper; ++i) {
            sum += piles[start + i - 1];
            result = max(result, sum + suffix_sum[start + i] -
                                     helper(start + i, max(M, i), piles, dp, suffix_sum));
        }
        return dp[start][M] = result;
    }
};

int main()
{

    vector<int> piles = { 2, 7, 9, 4, 4 };
    Solution s;
    cout << s.stoneGameII(piles) << endl;
    return 0;
}
