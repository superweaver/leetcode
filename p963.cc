#include "common.h"
class Solution {
public:
	double minAreaFreeRect(vector<vector<int>>& points) {
		unordered_set<int> P;
		for (auto&v : points) {
			P.insert((v[0] << 16) + v[1]);
		}
		double r = numeric_limits<double>::max();
		int n = points.size();
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				for (int k = j + 1; k < n; ++k) {
					double area;
					if (check(points[i], points[j], points[k], area, P)) {
						r = min(r, area);
					}
				}
			}
		}
		if (r == numeric_limits<double>::max()) {
			return 0;
		}
		else {
			return r;
		}
	}
private:
	bool check(vector<int>&a, vector<int>&b, vector<int>&c, double& area, unordered_set<int>&P) {
		int x1 = b[0] - a[0];
		int y1 = b[1] - a[1];
		int x2 = c[0] - a[0];
		int y2 = c[1] - a[1];
		if (x1*x2 + y1 * y2 == 0) {
			int last_x = c[0] + b[0] - a[0];
			if (last_x >= 0 && last_x <= 40000) {
				int last_y = c[1] + b[1] - a[1];
				if (last_y >= 0 && last_y <= 40000) {
					if (P.count((last_x << 16) + last_y)) {
						area = fabs(x1*y2 - x2 * y1);
						return true;
					}
				}
			}
		}
		//
		x1 = a[0] - b[0];
		y1 = a[1] - b[1];
		x2 = c[0] - b[0];
		y2 = c[1] - b[1];
		if (x1*x2 + y1 * y2 == 0) {
			int last_x = c[0] + a[0] - b[0];
			if (last_x >= 0 && last_x <= 40000) {
				int last_y = c[1] + a[1] - b[1];
				if(last_y >= 0 && last_y <= 40000) {
					if (P.count((last_x << 16) + last_y)) {
						area = fabs(x1*y2 - x2 * y1);
						return true;
					}
				}
			}

		}
		//
		x1 = a[0] - c[0];
		y1 = a[1] - c[1];
		x2 = b[0] - c[0];
		y2 = b[1] - c[1];
		if (x1*x2 + y1 * y2 == 0) {
			int last_x = b[0] + a[0] - c[0];
			if (last_x >= 0 && last_x <= 40000) {
				int last_y = b[1] + a[1] - c[1];
				if (last_y >= 0 && last_y <= 40000) {
					if (P.count((last_x << 16) + last_y)) {
						area = fabs(x1*y2 - x2 * y1);
						return true;
					}
				}

			}

		}
		return false;
	}
};

int main() {

	Solution s;

	return 0;
}
