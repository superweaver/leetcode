#include "common.h"
class Solution {
public:
    int distinctSubseqII(string S) {
        int n = S.size();
        const int Mod = 1000000007;
        vector<int> lastIndex(128, -1);
        //vector<int> dp(n + 1, 0); // how many different Subseqences with first len characters
        vector<int> dp(1, 0); // how many different Subseqences with first len characters
        // case 1:
        // new character doesn't appear before
        // dp[i] = dp[i] + (dp[i] + 1); the later is appending new character to dp[i]
        // case 2: 
        // k0, k1, k2, ...km are previous index of new character
        // upto k0, the subsequences has no character c
        // from k0 to k1-1, the change of dp only counts subsequences of 1 character c
        // when we try to append it subsequences with zero c, it must have been included into above above sequences of 1 c
        // so we should only append c to the subsequencies of (m + 1) character of c_s;
        for (int i = 0; i < n; ++i) {
            char c = S[i];
            if (lastIndex[c] < 0) {
                dp[i + 1] = (dp[i] * 2 + 1) % Mod;
            } else {
                int pre = lastIndex[c];
                int delta = (dp[i] - dp[pre] + Mod) % Mod; // how many subsequencies have (m+1) c,
                // append the new c to the end of them
                dp[i + 1] = (dp[i] + delta) % Mod; 
            }
            lastIndex[c] = i; 
        }
        return dp[n];
    }
};

int main() {
    vector<string> input = {"abc", "aba", "aaa", "zchmliaqdgvwncfatcfivphddpzjkgyygueikthqzyeeiebczqbqhdytkoawkehkbizdmcnilcjjlpoeoqqoqpswtqdpvszfaksn"};
    Solution s;
    for (auto & str : input) {
       cout << str << ":" <<  s.distinctSubseqII(str) << endl;
    }
    return 0;
}
