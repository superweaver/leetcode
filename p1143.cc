#include "common.h"
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
		// dp[i][j] is the length of longest common subsequence of substring text1[0..i)
		// and substring text2[0..j)
		// if text1[i] == text2[j] then  dp[i][j] = 1 + dp[i-1][j-1]
		// if text1[i] != text2[j], then dp[i][j] = max(dp[i-1][j], dp[i][j-1])
		// return dp[m][n]
        string* p1 = &text1;
        string* p2 = &text2;
		if (p1->size() > p2->size()) {
			swap(p1, p2);
		}
		// p1->size() <= p2->size();
		int m = p1->size();
		int n = p2->size();
        vector<int> dp(n + 1, 0);
        vector<int> pre(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
			pre.swap(dp);
            for (int j = 1; j <= n; ++j) {
                if (p1->at(i - 1) == p2->at(j - 1)) {
                    dp[j] = pre[j - 1] + 1;
                } else {
                    dp[j] = max(dp[j - 1], pre[j]);
                }
            }
        }
        return dp[n];
    }
};

int main() {
    string text1 = "abcde", text2 = "ace";
    Solution s;
	cout << s.longestCommonSubsequence(text1, text2) << endl;
	return 0;
}
