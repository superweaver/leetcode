#include "common.h"
class Solution {
public:
    int numPermsDISequence(string S)
    {
        /*
         * Input: "DID"
         * Output: 5
         * Explanation:
         * The 5 valid permutations of (0, 1, 2, 3) are:
         * (1, 0, 3, 2)
         * (2, 0, 3, 1)
         * (2, 1, 3, 0)
         * (3, 0, 2, 1)
         * (3, 1, 2, 0)
         * */
        // dp[i][j] means # valid permutations for string of first i characters of S and the last
        // number of permuation is j dp[0][0] = 1;
        // if S[i-1] == 'I', dp[i][0] = 0;
        // then dp[i][j] = sum(dp[i-1][k]), k = 0...j-1, for number in these permutations, if add one if it is >= k
        // if S[i-1] == 'D', dp[i][i] = 0;
        // dp[i][j] = sum(dp[i-1][k]), i>=k>=j;
        const int Mod = 1000000007;
        int n = S.size();
        vector<vector<int>> dp(n + 1, vector<int>(n+1, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            if (S[i - 1] == 'I') {
                // dp[i][0] = 0;
                int sum = 0;
                for (int j = 1; j <= i; ++j) {
                    sum = (dp[i - 1][j - 1] + sum) % Mod;
                    dp[i][j] = sum;
                }
            } else {
                //dp[i][i] = 0;
                //int sum = dp[i-1][i]; // = 0
                int sum = 0; // = 0
                for (int j = i - 1; j >= 0; --j) {
                    sum = (sum + dp[i-1][j]) % Mod;
                    dp[i][j] = sum;
                    //dp[i][j] = dp[i][j + 1] + dp[i - 1][j];
                }
            }
        }
        int r = 0;
        auto&v = dp[n];
        for(auto i : v){
            r = (r + i ) % Mod;
        }
        return r;
    }
};



int main() {

	Solution s;

	return 0;
}
