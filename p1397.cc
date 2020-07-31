#include "common.h"
// https://www.cnblogs.com/wenruo/p/12616985.html
// hard
class Solution {
public:
    static const int mod = 1000000007;
    int findGoodStrings(int n, string s1, string s2, string evil) {
        int m = evil.size();
        // calculate next array for string evil
        int nt[m + 1];
        nt[0] = -1;
        for (int j = 0, k = -1; j < m;) {
            if (k == -1 || evil[j] == evil[k]) {
                nt[++j] = ++k;
            } else {
                k = nt[k];
            }
        }
        // done
        //
        // boundary condition for s1
        int f = s1.find(evil) == string::npos;

        return (cal(n, s2, evil, nt) - cal(n, s1, evil, nt) + f + mod) % mod;
    }


    int cal(int n, string &s, string &evil, int nt[]) {
        // calculate number of strings which are <= s, which doesn't include eveil
        int m = evil.size();
        int dp[n + 1][m][2];
        // dp[i][j][0] 前i个字符 of s 和evil有j个相同; 0不和s相等 1和s相等
        memset(dp, 0, sizeof dp);
        dp[0][0][1] = 1; // base case

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (char c = 'a'; c <= 'z'; c++) {
                    int len = getNextLen(evil, nt, j, c);
                    if (len < m) { // !!!
                        if (c < s[i]) {
                            // old = becomes new <
                            up(dp[i+1][len][0], dp[i][j][1]);
                            // old < is still <
                            up(dp[i + 1][len][0], dp[i][j][0]);
                        } else if (c == s[i]) {
                            // old = becomes new =
                            up(dp[i + 1][len][1], dp[i][j][1]);
                            // old < is still <
                            up(dp[i + 1][len][0], dp[i][j][0]);
                        } else {
                            // only old < is still <
                            up(dp[i + 1][len][0], dp[i][j][0]);
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < m; i++) {
            up(ans, dp[n][i][0]);
            up(ans, dp[n][i][1]);
        }
        return ans;
    }

    int getNextLen(string &evil, int nt[], int len, char c) {
        while (len != -1 && evil[len] != c) {
            len = nt[len];
        }
        return len + 1;
    }
    void up(int &x, int add) {
        x = (x + add) % mod;
    }
};

int main() {

	Solution s;

	return 0;
}
