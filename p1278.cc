#include "common.h"
// https://leetcode.com/problems/palindrome-partitioning-iii/discuss/442083/Simple-C%2B%2B-Dp-O(N2K)-Beats-100-with-Explanation

class Solution {
public:
    int palindromePartition(string s, int k) {
        // two dp
        // dp[i][j] means the minimum changes needed to convert substring s[i..j] into a palindrome
        // dp_g[j][k] means the minimum changes need to convert substring s[0...j] into k sub palindrome
        // k >= 1
        //
        // connection:
        // dp[0][j] = dp_g[j][1]
        //
        //dp_g[j][k] = min(dp_g[J][k-1] + dp[J+1][j]) for 0 <= J  < j
        //
        //return dp_g[s.size()-1][k]
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, n));
        // order matters
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    if (len <= 2) {
                        dp[i][j] = 0;
                    } else {
                        dp[i][j] = dp[i+1][j-1];
                    }
                } else {
                    if (len <= 2) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = 1 + dp[i + 1][j - 1];
                    }
                }
            }
        }

        // second round
        vector<vector<int>> dp_g(n, vector<int>(k + 1, INT_MAX / 2));
        // ik = 1
        for (int j = 0; j < n; ++j) {
            dp_g[j][1] = dp[0][j];
        }
        // for ik >= 2
        for (int ik = 2; ik <= k; ++ik) {
            for (int j = 0; j < n; ++j) {
                if (j - 0 + 1 < ik) {
                    // ik > substring length
                    continue;
                }
                for (int J = 0; J < j; ++J) {
                    dp_g[j][ik] = min(dp_g[j][ik], dp_g[J][ik-1] + dp[J+1][j]);
                }
            }
        }
        return  dp_g[n-1][k];
    }
};

int main() {
    string s = "abc"; 
    int k = 2; // 1
    s = "aabbc", k = 3;// 0
    s = "aabbc", k = 2;// 0

	Solution so;
    cout << so.palindromePartition(s, k) << endl;

	return 0;
}
