#include "common.h"
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
		// Floyd-warshell algorithm
		const int Upper = 1010000;
		vector<vector<int>> dp(n, vector<int>(n, Upper));
		for (int i = 0; i < n; ++i) {
			dp[i][i] = 0;
		}
		for (auto &v : edges) {
			int s = v[0];
			int d = v[1];
			int w = v[2];
			dp[s][d] = dp[d][s] = w;
		}
		for (int mid = 0; mid < n; ++mid) {
			for (int s = 0;  s < n; ++s) {
				for (int d = 0; d < n; ++d) {
					if (dp[s][d] > dp[s][mid] + dp[mid][d]) {
                        dp[s][d] = dp[s][mid] + dp[mid][d];
                    }
				}
			}
		}
		int result = INT_MAX;
		int count = INT_MAX;
		for (int s = n - 1; s >= 0; --s) {
			auto &v = dp[s];
			int c = 0;
			for (int d = 0; d < n; ++d) {
				if (v[d] <= distanceThreshold) {
					c++;
					if (c >= count) {
						break;
					}
				}
			}
			if (c < count) {
				count = c;
				result = s;
			}
		}
		return result;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> edges = { { 0, 1, 3 }, { 1, 2, 1 }, { 1, 3, 4 }, { 2, 3, 1 } };
    int distanceThreshold = 4; // 3
    Solution s;
	cout << s.findTheCity(n, edges, distanceThreshold) << endl;
    return 0;
}
