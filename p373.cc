#include "common.h"
class Solution {
public:
  vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
      auto compare = [&](pair<int, int> a, pair<int, int> b) {
          return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
      };

      // note !!!  // type + obj
      priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> minHeap(compare);

      vector<vector<int>> res;
      int n = nums1.size(), m = nums2.size();
      if (!n || !m) {
          return res;
      }

      for (int i = 0; i < n; ++i) {
          minHeap.push(make_pair(i, 0));
      }

      while (k-- && !minHeap.empty()) {
          pair<int, int> cur = minHeap.top();
          minHeap.pop();
          res.emplace_back(vector<int>({nums1[cur.first], nums2[cur.second]})); // equal to
                                                                                // push_back
          // smart update
          if (cur.second + 1 < m) {
              minHeap.push(make_pair(cur.first, cur.second + 1));
          }
      }
      return res;
  }
};

int main() {

	Solution s;

	return 0;
}
