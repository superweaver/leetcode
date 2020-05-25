#include "common.h"
//https://www.cnblogs.com/grandyang/p/6188893.html
//https://www.youtube.com/watch?v=nleY0-eexps
//https://blog.csdn.net/stack_queue/article/details/53544109
// explaination:refer to the comments of https://www.cnblogs.com/grandyang/p/6188893.html
// extension //https://github.com/tianyicui/pack/blob/master/V2.pdf
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        // this is a 2d backpack problem !!!
        // hints: try to use DP to solve questions when they only require the total number instead of listing all of them
        // dp[i][j] means the max number of strings in strs that can be composed by i 0s and j 1s
        // for each string in strs, get its ones and zeros
        // dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones] + 1) if i >= zeros, j >= ones
        // original dp
        // k means use first k element of strs
        // dp[k][i][j] = max(dp[k-1][i][j],dp[k-1][i-zeros][j-ones])
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (string s : strs) {
            int ones = 0;
            for (char c : s) {
                ones += c - '0';
            }
            int zeros = s.size() - ones;
            // order is important, refer to explaination above
            // pay attention to boundary contion
            // i >= zeros and j >= ones !!!
            for (int i = m; i >= zeros; --i) {
                for (int j = n; j >= ones; --j) {
                    //left side is for k
                    //right side is for k - 1
                    dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones] + 1);
                }
            }
        }
        return dp[m][n];
    }
};


int main() {

	Solution s;

	return 0;
}
