#include "common.h"
#include <functional>
//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1531-string-compression-ii/

int cache[101][27][101][101];
class Solution {
public:
    /*
     * State:
i: the start index of the substring
last: last char
len: run-length
k: # of chars that can be deleted.

base case:
1. k < 0: return inf # invalid
2. i >= s.length(): return 0 # done

Transition:
1. if s[i] == last: return carry + dp(i + 1, last, len + 1, k)

2. if s[i] != last:
return min(1 + dp(i + 1, s[i], 1, k, # start a new group with s[i]
dp(i + 1, last, len, k -1) # delete / skip s[i], keep it as is.

Time complexity: O(n^3*26)
Space complexity: O(n^3*26)
     */
  int getLengthOfOptimalCompression_long(string s, int k) {
      memset(cache, -1, sizeof(cache)); // not computed
      function<int(int, int, int, int)> dp = [&](int i, int last, int len, int k) -> int {
          if (k < 0) {
              return INT_MAX/2;
          }
          if (i >= s.size()) {
              return 0;
          }
          int &result = cache[i][last][len][k];
          if (result != -1) {
              return result;
          }
          if (last == s[i]-'a') {
              // same, then there is no need to delete current s[i]
              int carry = (len == 1) || (len == 9) || (len == 99);
              result = carry + dp(i + 1, last, len + 1, k);
          } else {
              // two choices
              // keep it
              // or delete it
              result = min(1 + dp(i + 1, s[i] - 'a', 1, k), /* keep it*/
                           dp(i + 1, last, len, k - 1)      /*delete it*/
              );
          }
          return result;
      };
      return dp(0, 26, 0, k);
  }
  /*
   * dp[i][k] := min len of s[i:] encoded by deleting at most k charchters.

dp[i][k] = min(dp[i+1][k-1] # delete s[i]
encode_len(s[i~j] == s[i]) + dp(j+1, k – sum(s[i~j])) for j in range(i, n)) # keep
   */

  int getLengthOfOptimalCompression(string s, int k) {
      const int n = s.length();
      vector<vector<int>> cache(n, vector<int>(k + 1, -1)); // not computed yet
      function<int(int, int)> dp = [&](int i, int k) -> int {
          if (k < 0) {
              return n; // INF
          }
          if (i + k >= n) { // it is enough to delete all of right characters
              return 0;
          }

          int &ans = cache[i][k];
          if (ans != -1) { // calculated, just return
              return ans;
          }
          // option 1 delete it
          ans = dp(i + 1, k - 1);
          // option 2 keep it
          int len = 0;
          int same = 0;
          int diff = 0;
          // diff <= k
          for (int j = i; j < n && diff <= k; ++j) {
              if (s[j] == s[i] && ++same) {
                  // carry
                  if (same <= 2 || same == 10 || same == 100) {
                      ++len;
                  }
              } else {
                  // delete all diff
                  ++diff;
              }
              ans = min(ans, len + dp(j + 1, k - diff));
          }
          return ans;
      };
      return dp(0, k);
  }
};

  int main() {
      string s = "aaabcccd";
      int k = 2;

      Solution so;
      cout << so.getLengthOfOptimalCompression(s, k) << endl;
      return 0;
}
