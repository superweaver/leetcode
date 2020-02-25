#include "common.h"
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        // find the longest common subsequence, then use it as frame
        // insert the remainder of str1 and str2 between characters of longet common subsequence
		str1.push_back('a');
		str2.push_back('a'); //  trick here
		reverse(str1.begin(), str1.end());;
		reverse(str2.begin(), str2.end());;
        vector<int> lcs;
		int m = str1.size();
		int n = str2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // the length of lcs for str1[0, m]
        // and str2[0, n]
        // dp[i][j]
        // dp[0][j] = 0;
        // dp[i][0] = 0;
        // if str1[i-1] == str1[j-1], then dp[i][j] = dp[i-1][j-1] + 1;
        // if str1[i-1] != str1[j-1], then dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
		for (int i = 1; i <= m ; ++i) {
			vector<int> next(n + 1, 0);
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }
        int i = m;
        int j = n;
		int length = dp[m][n];
		string result;
		while(true) {
            if (result.size() == size_t(m + n - dp[m][n])) {
                break;
            }
			// try	str1
			bool pushed = false;
            while (i >= 1) {
                if (dp[i][j] == length) {
                    result.push_back(str1[i - 1]);
					pushed = true;
                    --i;
                } else {
					break;
                }
            }
            if (pushed) {
				++i;
                result.pop_back();
            }
			pushed = false;
            while (j >= 1) {
                if (dp[i][j] == length) {
                    result.push_back(str2[j - 1]);
                    --j;
					pushed = true;
                } else {
					break;
                }
            }
            --i;
            --length;
        }
        //reverse(result.begin(), result.end());
		result.pop_back(); // pop the inserted 'a' out
		return result;
    }
};

int main() {
    string str1 = "abac", str2 = "cab";
    str1 = "kaedblc";
    str2 = "jafbmwcq";
    Solution s;
	cout << s.shortestCommonSupersequence(str1, str2) << endl;
	return 0;
}
