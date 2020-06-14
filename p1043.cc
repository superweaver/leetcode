#include "common.h"
class Solution {
  public:
    int maxSumAfterPartitioning(vector<int> &A, int K) {
        int n = A.size();
        vector<int> g(n + 1, 0); // the max sum we can get by using first i element
        g[0] = 0;                // base case !!!
        for (int i = 0; i < n; ++i) {
            // update futher g
            int peak = -1;
            for (int len = 1; len <= K; ++len) {
                // i - 1 is the last index of previous partition
                int j = i - 1 + len; // j is the last index of last segment
                if (j < n) {
                    peak = max(peak, A[j]);
                    g[i + len] = max(g[i + len], g[i] + peak * len);
                } else {
                    break;
                }
            }
        }
        return g[n];
    }
    int maxSumAfterPartitioning2(vector<int> &A, int K) {
        // my solution
        int n = A.size();
        vector<vector<int>> cache(n, vector<int>(K, 0)); // start at i , partion length = k + 1
        for (int i = 0; i < n; ++i) {
            int m = -1;
            for (int k = 0; k < K; ++k) {
                if (i + k >= n) {
                    break;
                }
                m = max(m, A[i + k]);
                cache[i][k] = (k + 1) * m;
            }
        }
        // dp[i][k] means the max sum we can get with first (i + 1) elements and the last partion length == k + 1
        // dp[i][k] < 0 means impossible
        // dp[i][k] = max(dp[i-k][m] + cache[i-k+1][k]); m = 0, ...K-1
        //			= g[i-k] + cache[i-k+1][k]

        vector<vector<int>> dp(n, vector<int>(K, -1));
        vector<int> g(n, 0); // g[i] = max(dp[i][k])
        g[0] = A[0];
        for (int i = 0; i < n; ++i) {
            // first i + 1 elements
            int lenUpper = min(i + 1, K);
            int temp = -1;
            for (int len = 1; len <= lenUpper; ++len) {
                // (i + 1) - len - 1 = i - len, is the last index of previous partition
                int pre = (i - len >= 0) ? g[i - len] : 0;
                int c = cache[i - len + 1][len - 1];
                temp = max(temp, dp[i][len - 1] = pre + c);
            }
            g[i] = temp;
        }
        return g[n - 1];
    }
};

int main() {

    vector<int> A = {1, 15, 7, 9, 2, 5, 10};
    int K = 3;

    Solution s;
    cout << s.maxSumAfterPartitioning(A, K) << endl;
    return 0;
}
