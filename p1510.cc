#include "common.h"
class Solution {
public:
  bool winnerSquareGame(int n) { 
      dp.assign(n + 1, -1);
      for (int i = 0; i * i <= n; ++i) {
          square.push_back(i * i);
      }
      int size = square.size();
      for (int i = 0; i <= n; ++i) {
          if (dp[i] == -1) {
              dp[i] = 0;
              for (int j = 1; j < size; ++j) {
                  int right = i + square[j];
                  if (right > n) {
                      break;
                  }
                  dp[right] = 1;
              }
          } else {
              continue;
          }
      }
      return dp[n] == 1;
  }

private:
    vector<int> dp;
    // dp[i] = 0, lose state
    // dp[i] = 1, win state
    // dp[i] is 1 if you can go to a lose state
    // dp[i] is 0 if it is impossible to go to a lose state
    // return dp[n]
    vector<int> square;
};

int main() {

	Solution s;
    for (int i = 1; i < 20; ++i) {
        cout << i << ":" << s.winnerSquareGame(i) << endl;
    }

	return 0;
}
