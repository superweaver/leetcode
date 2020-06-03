#include "common.h"
class Solution {
public:
       int uniqueLetterString(string S) {
        if (S.empty()) return 0;
        int n = S.size();
        const int Mod = 1000000007;
        long long r = 0;
        vector<int> dp(n, 0);
        // can be simplified to keep only last two previous index
        // -1, -2 can be used too
        vector<vector<int> > pre(128);  // previous index of certain char
        // dp[i] is the sum of unique(substring) ending at S[i]
        dp[0] = 1;
        pre[S[0]].push_back(0);
        r += dp[0];
        for (int i = 1; i < n; ++i) {
            auto& v = pre[S[i]];
            if(v.size() >= 2) {
                // this is general formula
                dp[i] = (dp[i - 1] - (v.back() - v[v.size() - 2])) + (i - v.back());
            } else if (pre[S[i]].size() == 1) {
                dp[i] = (dp[i - 1] - (v.back() + 1)) + (i - v.back());
            } else {
                dp[i] = dp[i - 1] + i + 1;
            }
            v.push_back(i);;
            r += dp[i];
            r %= Mod;
        }
        return r;
    }
};


int main() {

	Solution s;

	return 0;
}
