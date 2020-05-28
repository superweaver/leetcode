#include "common.h"

class Solution {
  public:
    // http://zxi.mytechroad.com/blog/dynamic-programming/leetcode-664-strange-printer/
    int strangePrinter(string s) {
        if (s.empty())
            return 0;
        int n = s.size();
        int pre = 0;
        for (int i = 1; i < n; ++i) {
            if (s[i] != s[pre]) {
                s[++pre] = s[i];
            }
        }
        s.resize(++pre);
        int result = 0;
        // remove  character with only one occurance
        unordered_map<char, int> count;
        for (auto c : s) {
            count[c]++;
        }
        n = 0;
        for (int i = 0; i < pre; ++i) {
            if (count[s[i]] != 1) {
                s[n++] = s[i];
            } else {
                result++;
            }
        }
        s.resize(n);
        vector<vector<int>> dp(n, vector<int>(n, 0));
        return result + helper(s, 0, n - 1, dp);
    }

  private:
    int helper(const string &s, int start, int end, vector<vector<int>> &dp) {
        if (start > end)
            return 0;
        if (dp[start][end] > 0)
            return dp[start][end];
        if (start == end) {
            dp[start][end] = 1;
            return 1;
        }

        int len = end - start + 1;
        dp[start][end] = len; // worst case
        for (int j = end - 1; j >= start; --j) {
            if (s[j] == s[end]) { // key!
                dp[start][end] = min(helper(s, start, j, dp) + helper(s, j + 1, end - 1, dp),
                                     dp[start][end]); // end -1 is the key, end was printed in
                                                      // helper(s, start, j) with s[j] == s[end]
            }
        }
        // another case
        dp[start][end] = min(helper(s, start, end - 1, dp) + 1, dp[start][end]);
        return dp[start][end];
    }
};

int main() {

	Solution s;

	return 0;
}
