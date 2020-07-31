#include "common.h"
// Author: Huahua
class Solution_huahua {
public:
  int closestToTarget(vector<int> &arr, int target) {
      const int n = arr.size();
      int ans = INT_MAX;
      for (int i = 0; i < n; ++i) { // left index
          int s = arr[i];
          for (int j = i; j < n; ++j) {
              s &= arr[j];
              ans = min(ans, abs(s - target));
              if (ans == 0) {
                  return 0;
              }
              if (s <= target) {
                  break; // s is decreasing.
              }
          }
          if (s > target) {
              // it has reached n-1
              // and it is still bigger than s
              // any new left index > than current i
              // will have s' >= s
              break; // s is increasing.
          }
      }
      return ans;
  }
};
class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        arr.erase(unique(arr.begin(),arr.end()), arr.end());
        int n = arr.size();
        int result = INT_MAX;
        for (int i = 0; i < n; ++i) { // i is right boundary
            if (arr[i] < target) {
                result = min(result, (target - arr[i]));
            } else if (arr[i] > target) {
                int temp = arr[i];
                result = min(result, abs(temp - target));
                for (int j = i - 1; j >= 0; --j) {
                    if (arr[j] < target) {
                        break;
                    }
                    temp &= arr[j];
                    result = min(result, abs(temp - target));
                    if (temp < target) {
                        break;
                    }
                }
                if (result == 0) {
                    return result;
                }
            } else {
                return 0;
            }
        }
        return result;
    }
};

int main() {
   vector<int> arr = {9,12,3,7,15};
   int target = 5; // 2
   //  arr = {1000000,1000000,1000000}, target = 1; // 9999
   //arr = {1,2,4,8,16}, target = 0; // 0

   Solution s;
   cout << s.closestToTarget(arr, target) << endl;

   return 0;
}
