#include "common.h"
// ref: // https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/discuss/709227/JavaC%2B%2BPython-Two-Sum

int numSubseq(vector<int> &A, int target) {
    sort(A.begin(), A.end());
    int res = 0, n = A.size(), l = 0, r = n - 1;
    const int mod = 1e9 + 7;

    vector<int> pows(n, 1);
    for (int i = 1; i < n; ++i) {
        pows[i] = pows[i - 1] * 2 % mod;
    }

    while (l <= r) {
        if (A[l] + A[r] > target) {
            // too big
            r--;
        } else {
            // ok
            // among A[i...j], we are free to pick or not element from [i+1, j]
            res = (res + pows[r - l]) % mod;
            l++;
        }
    }
    return res;
}

class Solution_my {
public:
  int numSubseq(vector<int> &nums, int target) {
      sort(nums.begin(), nums.end());
      long long result = 0;
      for (auto it = nums.begin(); it != nums.end(); ++it) {
          int y = min(*it, target - *it); // the other element can't exceed y
          auto upper = upper_bound(nums.begin(), it, y);
          // pre(upper) point to the max (min element)
          auto count = distance(nums.begin(), upper);
          // from nums.begin, to upper
          // you have (2^count)-1 choices, the 1 is the empty set
          auto right = distance(upper, it);
          // from upper to it, these elements are free to choice or not
          // 2^right
          if (count == 0) {
              if ((*it) * 2 <= target) {
                  result++;
                  continue;
              } else {
                  break;
              }
          }
          result += (get(count) - 1) * get(right) + (((*it) * 2 <= target) ? 1 : 0);
          result %= Mod;
      }
      return result;
  }
private:
  unordered_map<int, int> cache;
  const int Mod = 1e9 + 7;
  long long get(int d) {
      if (d < 0) {
          return 0;
      }
      if (d == 0) {
          return 1;
      }
      // return 2^d % Mod;
      if (cache.count(d)) {
          return cache[d];
      } else {
          int half = d / 2;
          long long vhalf = get(half);
          long long v = vhalf;
          v *= vhalf;
          if (d & 1) {
              v *= 2;
          }
          v %= Mod;
          return cache[d] = v;
      }
  }
};

int main() {
    vector<int>nums = {5,2,4,1,7,6,8};
    int target = 16; // 127

    nums = {2,3,3,4,6,7}, target = 12;// 63
    nums = {3,3,6,8}, target = 10; // 6
    nums = {3,5,6,7}, target = 9; // 4



	Solution s;
    cout << s.numSubseq(nums, target) << endl;

	return 0;
}
