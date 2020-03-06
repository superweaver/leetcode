#include "common.h"
class Solution {
public:
    double angleClock(int hour, int minutes) {
		//	1 <= hour <= 12
		// 0 <= minutes <= 59
        double theta_h = ((hour % 12) + minutes / 60.0) * 360 / 12.0; // !!!
        double theta_m = double(minutes * 360 / 60.0);
		double result = abs(theta_h - theta_m);
		result = min(result, 360 - result);
        return result;
    }
};

int main() {
    int hour = 12;
    int minutes = 30; // 165
	hour = 3, minutes = 30; // 75
	hour = 3, minutes = 15; // 7.5
	hour = 4, minutes = 50; // 155
	hour = 12, minutes = 0; // 0


    Solution s;
	cout << s.angleClock(hour, minutes) << endl;
	return 0;
}
