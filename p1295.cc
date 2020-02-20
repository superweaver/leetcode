#include "common.h"
class Solution {
public:
    int findNumbers(vector<int>& nums) {
		int count = 0;
		for (auto n : nums) {
            int digits = 0;
            while (n) {
                digits++;
				n /= 10;
            }
            if (digits > 0 && !(digits & 1)) {
                count++;
            }
        }
		return count;
    }
};

int main() {

	vector<int> nums = {12,345,2,6,7896};
	Solution s;
	cout << s.findNumbers(nums) << endl;
	return 0;
}
