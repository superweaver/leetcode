#include "common.h"
class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> dp(n, 0); // not calculated
        // dp[i] means starting from i, the max number of indices you can get
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            result = max(result, helper(arr, dp, i, n, d));
        }
        return result;
    }
private:
  int helper(vector<int>& arr, vector<int> &dp, int index, int n, int d) {
      if(index >= n || index < 0) {
          return 0;
      }
      if (dp[index] > 0) {
          return dp[index];
      }
      int candidate = 0;
      // order matters
      // go left from higher index to lower index
      for (int len = 1; len <= d; ++len) {
          int i = index - len;
          if (i < 0) {
              break;
          }
          if (arr[i] >= arr[index]) {
              break;
          }
          candidate = max(candidate, helper(arr, dp, i, n, d));
      }
      // go right fro lower index to higher index
      for (int len = 1; len <= d; ++len) {
          int i = index + len;
          if (i >= n) {
              break;
          }
          if (arr[i] >= arr[index]) {
              break;
          }
          candidate = max(candidate, helper(arr, dp, i, n, d));
      }
      return dp[index] = candidate + 1;
  }
};

int main() {
    vector<int> arr = {6,4,14,6,8,13,9,7,10,6,12};
    int d = 2; //4
    arr = {3, 3, 3, 3, 3}, d = 3; // 1
    arr = {7,6,5,4,3,2,1}, d = 1; // 7
    arr = {7,1,7,1,7,1}, d = 2; // 2
    arr = {22, 29, 52, 97, 29, 75, 78, 2, 92, 70, 90, 12, 43, 17, 97, 18, 58, 100, 41, 32};
    d = 17;

    Solution s;
    cout << s.maxJumps(arr, d) << endl;

	return 0;
}
