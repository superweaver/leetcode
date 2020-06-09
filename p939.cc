#include "common.h"

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
       sort(points.begin(), points.end());
       int n = points.size();

       unordered_set<int> cache;
       for(auto &v :points) {
           cache.insert(v[0] * n + v[1]);
       }
       int r = INT_MAX;
       for (int i = 0; i < n; ++i) {
           int x_i = points[i][0];
           int y_i = points[i][1];
           for (int j = i + 1; j < n; ++j) {
               int x_j = points[j][0];
               int y_j = points[j][1];
               if ((x_j > x_i && y_j > y_i)) {
                   if (cache.count(x_i * n + y_j) && cache.count(x_j * n + y_i)) {
                       r = min(r, (x_j - x_i) * (y_j - y_i));
                   }
               }
           }
       }
       return r == INT_MAX ? 0 : r;
    }
};


int main() {

	Solution s;

	return 0;
}
