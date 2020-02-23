#include "common.h"
class Solution {
public:
    int dayOfYear(string date) {
		//Input:date = "2019-01-09" Output : 9
		int year = atoi(date.substr(0, 4).c_str());
		int month = atoi(date.substr(5, 2).c_str());
		int day = atoi(date.substr(8, 2).c_str());
		bool leap = false;
        if (year % 4 == 0) {
            leap = true;
			if (year % 100 == 0) {
                if (year % 400 == 0) {
                    leap = true;
                } else {
                    leap = false;
                }
            }
        }
        int result = 0;
		for (int i = 0; i < month - 1; ++i) {
			result += days[i];
		}
		if (month > 2) {
			result += leap;
		}
		return result += day;
    }
private:
    vector<int> days{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};

int main() {

	string date = "2019-01-09"; // 9
	date = "2003-03-01"; // 60
	date = "2004-03-01"; // 61
	date = "1900-03-01";
	Solution s;
	cout << s.dayOfYear(date) << endl;
	return 0;
}
