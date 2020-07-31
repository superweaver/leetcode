#include "common.h"
class Solution {
public:
  // https://www.youtube.com/watch?v=g2jmxEzwtv0
  int minNumberOfSemesters(int n, vector<vector<int>> &dependencies, int k) {
      // totally there 1<<n states from [0, (1<<n) -1]
      // dp[s] is the minimum number of semesters to achieve state s
      // dp[0] = 0
      // return dp[(1<<n)-1]
      // transition
      // dp[s] = min(dp[s], dp[sp] + 1);
      // requirement
      // (1) sp must be a true subset of s (sp&s == sp)
      //                                 so that sp < s
      // (2) 0 < popcount(s) - popcount(sp) <= k, at most k courses can be added in one semester
      // (3) all s's prerequistes are in sp
      int N = 1 << n;
      vector<int> dp(N, INT_MAX);
      dp[0] = 0;
      vector<int> prerequistes(n, 0); // course's prerequistes
      for (auto d : dependencies) {
          int from = d[0] - 1;
          int to = d[1] - 1;
          prerequistes[to] |= (1 << from);
      }
      //calculate prerequistes of state
      vector<int> preStates(N, 0);
      for (int s = 1; s < N; ++s) {
          for (int i = 0; i < n; ++i) {
              if ((1 << i) & s) {
                  // course i is in s
                  preStates[s] |= prerequistes[i];
              }
          }
      }
      for (int s = 1; s < N; ++s) {
          // get all subset of s
          for (int subset = s;; subset = (subset - 1) & s) { // condition(1)
              if (subset == s) {                             // need to be a true subset
                  continue;
              }
              if (__builtin_popcount(s) - __builtin_popcount(subset) <= k &&
                  ((preStates[s] & subset) == preStates[s])) {
                  dp[s] = min(dp[s], dp[subset] + 1);
              }
              if (subset == 0) { // this is a valid state, and there is no more valid states
                  break;
              }
          }
      }
      return dp[N - 1];

    }
};

int main() {
    int n = 5;
    vector<vector<int>> dependencies = {{2,1},{3,1},{4,1},{1,5}}; 
    int k = 2;//4
    n = 11, dependencies = {}, k = 2; //6

	Solution s;
    cout << s.minNumberOfSemesters(n, dependencies, k) << endl;

	return 0;
}
