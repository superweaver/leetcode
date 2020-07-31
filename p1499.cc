#include "common.h"
class Solution {
public:
    int findMaxValueOfEquation_original(vector<vector<int>>& points, int k) {
       // can be improved
       // only need to stroe index instead of value
       //
        // for i < j
        // we have xi < xj
        //
        // f = yi + yj + |xi - xj|
        // subject to
        // |xi - xj| <= k
        // and 1<=i< j <= points.length
        // i < j, then xi < xj
        // then f = yi + yj + xj - xi
        // for any xj, yj
        // f = (xj + yj) + (yi - xi)
        //
        // store (xi, yi-xi) as pair
        // need bigger yi-xi, and expect larger xi for candidate
        deque<pair<int, int>> q;
        int n = points.size();
        q.push_back({points[0][0], points[0][1] - points[0][0]});
        int result = INT_MIN;
        for(int j = 1; j < n; ++j) {
            while(!q.empty() && q.front().first + k < points[j][0]) {
                 q.pop_front();
            }
            if (!q.empty()) {
                result = max(result, q.front().second + points[j][0] + points[j][1]);
            }
            int v = points[j][1] - points[j][0];
            while(!q.empty() && v>= q.back().second) {
                q.pop_back();
            }
            q.push_back({points[j][0], v});
        }
        return result;
    }
    int findMaxValueOfEquation(vector<vector<int>> &points, int k) {
        deque<int> q; // store index
        int n = points.size();
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            while(!q.empty() && points[q.front()][0] + k < points[i][0]) {
                q.pop_front();
            }
            if (!q.empty()) {
                result = max(result, points[q.front()][1] - points[q.front()][0] + points[i][0] +
                                         points[i][1]);
            }
            int c = points[i][1] - points[i][0];
            while (!q.empty() && (c >= points[q.back()][1] - points[q.back()][0])) {
                q.pop_back();
            }
            q.push_back(i);
        }
        return result;
    }
};

int main() {
    vector<vector<int>> points = {{1,3},{2,0},{5,10},{6,-10}}; //4
    int k = 1;
    //points = {{0,0},{3,0},{9,2}}, k = 3; // 3

	Solution s;
    cout << s.findMaxValueOfEquation(points, k) << endl;

	return 0;
}
