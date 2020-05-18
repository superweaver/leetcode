#include "common.h"
class Solution {
  public:
      // not solved
      // https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/discuss/636416/c%2B%2B-O(n2logn)-angular-sweep-(with-picture)
    int numPoints(vector<vector<int>> &p, int r) {
        int n = p.size();
        vector<vector<double>> dist(n, vector<double>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = dist[j][i] = sqrt((p[i][0] - p[j][0]) * (p[i][0] - p[j][0]) +
                                               (p[i][1] - p[j][1]) * (p[i][1] - p[j][1]));
            }
        }

        int res = 1;
        for (int i = 0; i < n; ++i) {
            vector<pair<double, bool>> angles;

            for (int j = 0; j < n; ++j) {
                if (j != i && dist[i][j] <= 2 * r) {
                    double A = atan2(p[j][1] - p[i][1], p[j][0] - p[i][0]);
                    double B = acos(dist[i][j] / (2.0 * r));
                    double alpha = A - B;
                    double beta = A + B;
                    angles.push_back(
                        make_pair(alpha, false));            // "false" means this point is entering
                    angles.push_back(make_pair(beta, true)); // "true" means this point is exiting
                }
            }

            sort(angles.begin(), angles.end()); // sort the angles

            int cnt = 1;
            for (auto it = angles.begin(); it != angles.end(); ++it) {
                if ((*it).second == false)
                    cnt++; // if the point is entering, then increment
                else
                    cnt--; // if it is exiting, then decrement

                res = max(res, cnt);
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> points = {{-2, 0}, {1, 1}, {1, 1}, {-2, 0}, {2, 0}, {0, 2}, {0, -2}};
    int r = 2;
    points = {{-2, 0}, {2, 0}, {0, 2}, {0, -2}};
    r = 1;
    points = {{5, 5}, {-2, 5}, {4, 2}, {1, -1}, {1, 1}};
    r = 5;

    Solution s;
    cout << s.numPoints(points, r) << endl;
    return 0;
}
