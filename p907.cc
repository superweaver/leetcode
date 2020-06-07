#include "common.h"
class Solution {
public:
    //https://zxi.mytechroad.com/blog/stack/leetcode-907-sum-of-subarray-minimums/
    // Author: Huahua, 60 ms
  int sumSubarrayMins_hua(vector<int> &A) {
      constexpr int kMod = 1e9 + 7;
      const int n = A.size();
      vector<int> left(n);  // left[i] is the length of subarray whose minimum is A[i] and subarray
                            // ends at index i
      vector<int> right(n); // right[i] is the length of subarray whose minimum is A[i] and subarray
                            // begins at index i
      stack<pair<int, int>> s; // len can be replaced by index
      int ans = 0;
      for (int i = 0; i < n; ++i) {
          int len = 1;
          while (!s.empty() && s.top().first > A[i]) {
              len += s.top().second;
              s.pop();
          }
          s.emplace(A[i], len);
          left[i] = len; 
      }

      while (!s.empty()) {
          s.pop();
      }
      for (int i = n - 1; i >= 0; --i) {
          int len = 1;
          while (!s.empty() && s.top().first >= A[i]) {
              len += s.top().second;
              s.pop();
          }
          s.emplace(A[i], len);
          right[i] = len;
      }
      for (int i = 0; i < n; ++i) {
          // this is good
          // how many subarrys can will use A[i] as minimum?
          // left[i] * right[i]
          ans = (ans + static_cast<long>(left[i]) * A[i] * right[i]) % kMod;
      }
      return ans;
  }

  int sumSubarrayMins(vector<int> &A) {
      int n = A.size();
      s.push({0, A[0]});
      long long r = s.top().second;
      // consider an element A[i] at index i
      // find first element that it smaller than A[i]
      for (int i = 1; i < n; ++i) {
          if (A[i] >= A[s.top().first]) {
              // s.top().first must be  i-1 ?
              // so any subarray ending at i
              // are either A[i] alone or whose minimum has been covered in subarray ending at s.top().first
              s.push({i, s.top().second + A[i]});
              r += s.top().second;
              r %= Mod;
          } else {
              while (!s.empty() && A[s.top().first] > A[i]) {
                  s.pop(); // this is good
              }
              if (s.empty()) {
                  s.push({i, A[i] * (i + 1)});
              } else {
                  s.push({i, A[i] * (i - s.top().first) + s.top().second});
              }
              r += s.top().second;
              r %= Mod;
          }
      }
      return (int)r;
  }

private:
	const int Mod = 1000000007;
    stack<pair<int, int>> s; // index in A and the sum of min(B) where B end at that index
};

int main() {
    vector<int> nums = {3, 1, 2, 4};

    Solution s;
    cout << s.sumSubarrayMins(nums) << endl;
	return 0;
}
