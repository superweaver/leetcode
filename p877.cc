#include "common.h"
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        // piles.size is odd
        int n = piles.size();
        vector<int> prefixsum(n + 1, 0);
        for (size_t i = 1; i < prefixsum.size(); ++i) {
            prefixsum[i] = piles[i-1] + prefixsum[i - 1];
        }
        // dp[i][j] is the max stones who can get by picking first
        // then the other can get sum[i...j] - dp[i][j]
        // dp[i][j] = max(p[i] + sum[i+1...j] - dp[i+1][j], p[j] + sum[i...j-1] - dp[i][j-1])
        // dp[i][j] = max(sum[i..j]-dp[i+1][j], sum[i..j]-dp[i][j-1])
        vector<vector<int> > dp(n, vector<int>(n, 0));
        int stone = getstones(dp, 0, n-1, prefixsum);
        return stone > prefixsum.back() - stone;
    }
private:
    int getstones(vector<vector<int> >& dp, int start, int end, const vector<int>& prefixsum)
    {

        if (start == end) {
            return dp[start][end] = prefixsum[start + 1] - prefixsum[start];
        }
        if (dp[start][end] > 0) {
            return dp[start][end];
        }
        int sum = prefixsum[end + 1] - prefixsum[start];
        return dp[start][end] = sum - min(getstones(dp, start + 1, end, prefixsum),
                                          getstones(dp, start, end - 1, prefixsum));
    }
};


int main() {

	Solution s;

	return 0;
}
