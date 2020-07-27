#include "common.h"
// ref
// https://leetcode.com/problems/dice-roll-simulation/discuss/423808/C%2B%2BJava-two-dimensional-DP-with-explanation

class Solution_ref2 {
    /*
     * DP[i][j] means the total number of combinations at round i we get a j at current round, considering the constraint.

Explanation
Let J be any integer in 1 to 6, and the maximum roll amount be k, then at round i we only allow:
J^CJ,  -> DP[i-1][j^C]
J^CJJ,
...,
J^CJJ...J, (k consecutive J)  -> DP[i-k][j^C]
where J^C represents a number that is not J, namely the complementary set of J.

DP approach
It is not difficult to see that DP[i][j] = DP[i-k][j^C] + ... + DP[i-1][j^C]. Upon noticing that DP[i][j^c] = sum[i] - DP[i][j], where sum[i] represents total number of combinations at round i considering the constraint, we end up with a two-dimensional DP, and an additional one-dimensional DP to quickly obtain sum[i].

The code should be pretty self-explanatory.
     */
  public:
    int dieSimulator(int n, vector<int> &rollMax) {
        // https://leetcode.com/problems/dice-roll-simulation/discuss/423808/C%2B%2BJava-two-dimensional-DP-with-explanation
        // nice explanation
        long Mod = 1e9 + 7;
        vector<vector<long>> dp(n+1, vector<long>(6, 0));
        // dp[i][j] is the total combinations at round[i] while current roll is j, considering constraint
        vector<long> sum(n+1, 0);
        // sum[i] = sum(dp[i][j] over j)
        // one way in the inital state
        sum[0] = 1;
        for (int i = 1; i <= n; ++i) { // round
            for (int j = 0; j < 6; ++j)  { // current roll
                // k is length of past rolled j
                // (sum[i - k] - dp[i - k][j]) is how many ways to state from which it can have k continusous j
                for (int k = 1; k <= rollMax[j] && i - k >= 0; ++k) {
                    dp[i][j] = (dp[i][j] + (sum[i - k] - dp[i - k][j]) + Mod) % Mod;
                }
                sum[i] = (sum[i] + dp[i][j]) % Mod;
            }
        }
        return sum[n];
    }
};

class Solution_ref {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        //dp[i][j][k]: i rolls, last one is j repeating k times
        int mx = *max_element(rollMax.begin(), rollMax.end());
        vector<vector<int>> dp(n + 1, vector<int>(6));
        int kMod = 1e9 + 7;
        vector<int> sums(n + 1);
        // rollMax[i] >= 1
        // base case
        for (int j = 0; j < 6; ++j) {
            dp[1][j] = 1;
            sums[1] += 1;
        }
        // run simulation
        for (int i = 2; i <= n; ++i) {
            // current roll is j
            for (int j = 0; j < 6; ++j) {
                // look back
                const int k = i - rollMax[j];
                const int invalid = (k <= 1) ? max(k, 0) : (sums[k - 1] - dp[k - 1][j]);

                dp[i][j] = ((sums[i - 1] - invalid) % kMod + kMod) % kMod;
                sums[i] = (sums[i] + dp[i][j]) % kMod;
            }
        }

        return sums[n];
    }
};

class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        // after n steps,
        // dp[i][j] means how many different ways to achieve current state which has j times of dice i+1 at the end of sequence
        // from this starting point
        // derive dp[i][j+1]
        //
        const int Mod = 1e9 + 7;
        vector<vector<int>> dp(6);
        // base case
        // for n == 1
        for (int i = 0; i < 6; ++i) {
            int upper = rollMax[i];
            dp[i].assign(upper + 1, 0);
            dp[i][1] = 1;
        }
        for (int k  = 1; k < n; ++k) {
            // current roll is i + 1
            vector<vector<int>> next(dp);
            for (auto &n : next) {
                for (auto& c : n) {
                    c = 0;
                }
            }

            for (int i = 0; i < 6; ++i) {
                for (int ii = 0; ii < 6; ++ii) {
                    for (int j = 0; j <= rollMax[ii]; ++j) {
                        int len = 1; //current len;
                        if (i == ii) {
                            len += j; // append to previous length
                        }
                        if (len > rollMax[i]) {
                            continue;
                        } else {
                            next[i][len] += dp[ii][j];
                            next[i][len] %= Mod;
                        }
                    }
                }
            }
            swap(next, dp);
        }
        int result = 0;
        for (auto n : dp) {
            for (auto c : n) {
                result += c;
                result %= Mod;
            }
        }
        return result;
    }
};

int main() {
    int n = 2;
    vector<int> rollMax = {1,1,2,2,2,3}; // 34
    //n = 3, rollMax = {1, 1, 1, 1, 1, 1}; // 30
    n = 3, rollMax = {1,1,1,2,2,3}; // 181
    n = 3, rollMax = {1,1,1,15,2,3}; // 182

	Solution s;
    cout << s.dieSimulator(n, rollMax) << endl;
	return 0;
}
