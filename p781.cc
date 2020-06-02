#include "common.h"
class Solution {
public:
  int numRabbits(vector<int> &answers) {
      // we can also use vector for caching
      unordered_map<int, int> count; // size -> apperances
      for (auto i : answers) {
          count[i+1]++;
      }
      int r = 0;
      for (auto &p : count) {
          int size = p.first;
          int apperances = p.second;
          r += ((apperances + size - 1) / size) * size;
      }
      return r;
  }

  int numRabbits_my(vector<int> &answers) {
      set<pair<int, int>> groupSize; // size, and apperances
      for (auto i : answers) {
          auto it = groupSize.lower_bound({i + 1, 0});
          if (it == groupSize.end()) {
              groupSize.insert({i + 1, 1});
          } else {
              if (it->first == i + 1) {
                  auto p = *it;
                  p.second++;
                  groupSize.erase(it);
                  groupSize.insert(p);
              } else {
                  groupSize.insert({i + 1, 1});
              }
          }
      }
      int r = 0;
      for (auto &p : groupSize) {
          if (p.second > p.first) {
              int times = p.second / p.first;
              if (p.first * times == p.second) {
                  r += p.second; // == p.first * times
              } else {
                  r += (times + 1) * p.first;
              }
          } else {
              r += p.first;
          }
      }
      return r;
	}
};

int main() {

	Solution s;

	return 0;
}
