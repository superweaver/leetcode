#include "common.h"
class Solution {
public:
    int balancedStringSplit(string s) {
		int count = 0;
		int result = 0;
		for (auto c : s) {
			if (c == 'L') {
				count++;
			} else {
				count--;
			}
			result += (!count);
		}
		return result;
    }
};

int main() {

	string str = "RLRRRLLRLL";
	Solution s;
	cout << s.balancedStringSplit(str) << endl;
	return 0;
}
