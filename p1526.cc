#include "common.h"
// ref:
// https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/discuss/754623/Detailed-Explanation
class Solution {
  public:
    int minNumberOperations(vector<int> &target) {
        int n = target.size();
        // assume previous height is pre
        // current height is current
        // case 1)
        // if pre >= current
        // we can reuse current
        // case 2)
        // if pre < current
        // when build current, current-pre must be added into operations
        // current can be reused later
        int reuse = 0;
        int result = 0;
        for (auto h : target) {
            if (reuse < h) {
                result += h - reuse;
                reuse = h; // case 2
            } else {
                reuse = h; // case 1
                // reuse is lower
            }
        }
        return result;
    }
};

class Solution_fail {
public:
  int minNumberOperations(vector<int> &target) {
      map<int, vector<pair<int, int>>> cache;
      int n = target.size();
      for (int i = 0; i < n; ++i) {
         int v = -target[i];
         if (cache.count(v)) {
             if (cache[v].back().second == i) {
                 cache[v].back().second++;
             } else {
                 cache[v].push_back({i, i + 1});
             }
         } else {
             cache[v].push_back({i, i + 1});
         }
      }
      cache[0] = {};
      int result = 0;
      // Time Limit Exceed
      for (auto it = cache.begin(); next(it) != cache.end(); ++it) {
          auto v1 = -it->first;
          auto& I1 = it->second;
          auto second = next(it);
          auto &I2 = second->second;
          auto v2 = -(second->first);
          // merge two intervales
          vector<pair<int, int>> intervals;
          int i1 = 0;
          int i2 = 0;
          pair<int, int> *p = nullptr;
          while(i1 < I1.size() ||  i2 < I2.size()) {
              if (i1 < I1.size() && i2 < I2.size()) {
                  if (I1[i1].first < I2[i2].first) {
                      p = &I1[i1++];
                  } else {
                      p = &I2[i2++];
                  }
              } else if (i1 < I1.size()) {
                  p = &I1[i1++];
              } else {
                  p = &I2[i2++];
              }
              if (intervals.empty()) {
                  intervals.push_back(*p);
              } else {
                  if (intervals.back().second == p->first) {
                      intervals.back().second = p->second;
                  } else {
                      intervals.push_back(*p);
                  }
              }
          }
          result += it->second.size() * (v1 - v2);
          second->second.swap(intervals);
      }
      return result;
  }
};

int main() {
    vector<int> target = {1,2,3,2,1}; //3
    target = {3,1,1,2}; //4
    target = {3,1,5,4,2}; // 7
    target = {10, 2, 7, 56, 37, 2, 7}; // 69



	Solution s;
    cout << s.minNumberOperations(target) << endl;

	return 0;
}
