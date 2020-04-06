#include "common.h"
class Solution {
public:
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {

        if (y_center >= y1 && y_center <= y2) {
			if (x_center >= x1 - radius && x_center <= x2 + radius) {
				return true;
			}
        }
		if (x_center >= x1 && x_center <= x2) {
			if (y_center>= y1 - radius && y_center <= y2 + radius) {
				return true;
			}
		}
		int r2 = radius * radius;
        if (x_center <= x1 && y_center >= y2) {
            x_center -= x1;
            y_center -= y2;
            return x_center * x_center + y_center * y_center <= r2;
        }
        if (x_center <= x1 && y_center <= y1) {
            x_center -= x1;
            y_center -= y1;
            return x_center * x_center + y_center * y_center <= r2;
        }
        if (x_center >= x2 && y_center >= y2) {
            x_center -= x2;
            y_center -= y2;
            return x_center * x_center + y_center * y_center <= r2;
        }
        if (x_center >= x2 && y_center <= y1) {
            x_center -= x2;
            y_center -= y1;
            return x_center * x_center + y_center * y_center <= r2;
        }
        return false;
    }
};

int main() {
	int radius = 1, x_center = 0, y_center = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1;
	radius = 1, x_center = 0, y_center = 0, x1 = -1, y1 = 0, x2 = 0, y2 = 1;
//	radius = 1, x_center = 1, y_center = 1, x1 = -3, y1 = -3, x2 = 3, y2 = 3;
//	radius = 1, x_center = 1, y_center = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1; // false

	Solution s;
	cout << s.checkOverlap(radius, x_center, y_center, x1, y1, x2, y2) << endl;

	return 0;
}
