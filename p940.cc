#include "common.h"
// another
// https://leetcode.com/problems/distinct-subsequences-ii/discuss/192017/C%2B%2BJavaPython-4-lines-O(N)-Time-O(1)-Space
//
class Solution {
public:
     int distinctSubseqII_ref(string S) {
         /*
          * Init an array endswith[26]
endswith[i] to count how many sub sequence that ends with ith character.

Now we have N = sum(endswith) different sub sequence,
add a new character c to each of them,
then we have N different sub sequence that ends with c.

With this idea, we loop on the whole string S,
and we update end[c] = sum(end) + 1 for each character.

We need to plus one here, because "c" itself is also a sub sequence.
          * */
         long endsWith[26] = {}, mod = 1e9 + 7;
         for (char c : S) {
             // 1L
             endsWith[c - 'a'] = accumulate(begin(endsWith), end(endsWith), 1L) % mod;
         }
         return accumulate(begin(endsWith), end(endsWith), 0L) % mod;
    }
    int distinctSubseqII(string S) {
        int n = S.size();
        const int Mod = 1000000007;
        vector<int> lastIndex(128, -1);
        vector<int> dp(n + 1, 0); // how many different Subseqences with first len characters
        // vector<int> dp(1, 0); // how many different Subseqences with first len characters
        // case 1:
        // new character doesn't appear before
        // dp[i] = dp[i] + (dp[i] + 1); the later is appending new character to dp[i]
        // case 2:
        // k0, k1, k2, ...km are previous index of new character
        // upto k0, the subsequences has no character c
        // from k0 to k1-1, the change of dp only counts subsequences of 1 character c
        // when we try to append it subsequences with zero c, it must have been included into above
        // above sequences of 1 c so we should only append c to the subsequencies of (m + 1)
        // character of c_s;
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
