#include "common.h"
// https://leetcode.com/problems/queue-reconstruction-by-height/discuss/427157/Three-different-C%2B%2B-solutions.-from-O(n2)-to-O(nlogn).-faster-than-99.
// method 3
class Solution {
public:
  vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
      // sort people
      sort(people.begin(), people.end(), [](const vector<int> &a, const vector<int> &b) {
          if (a[0] != b[0]) {
              return a[0] < b[0];
          } else {
              // for the same height person
              // seconder larger one comes first
              return a[1] > b[1];
          }
      });
      int n = people.size();
      set<int> emptylocs;
      for (int i = 0; i < n; ++i) {
          emptylocs.insert(i);
      }
      vector<vector<int>> result(n);
      for (auto &p : people) {
          int loc = p[1];
          // find correct index
          auto it = next(emptylocs.begin(), loc);
          int index = *(it);
          result[index] = p;
          emptylocs.erase(it);
      }
      return result;
  }
};

// not solved
// http://www.cnblogs.com/grandyang/p/5928417.html
class Solution2 {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        // sort people by height
        // higher comes first
        // same height , smaller pair.second comes first
        sort(people.begin(), people.end(), [](const pair<int, int>& a, const pair<int, int>& b){
            return a.first > b.first || ((a.first == b.first)&&(a.second < b.second));
        });

        vector<pair<int, int>> result;
        // for person, p.second = k
        // then insert at kth position
        for(auto& p: people){
            result.insert(result.begin() + p.second, p);
        }
        return result;
    }
};

int main() {

    vector<vector<int>> people = {{7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2}};

	Solution s;
    auto r = s.reconstructQueue(people);
    for (auto &p : r) {
        cout << p[0] << " " << p[1] << endl;
    }
	return 0;
}
