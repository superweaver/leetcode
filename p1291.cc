#include "common.h"
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
		set<int> result;	
		for (int i  = 1; i <= 8; ++i) {
			int candidate = 0;
			for (int j = i; j < 10; ++j) {
				candidate = candidate * 10 + j;
				if (candidate >= low && candidate <= high) {
					result.insert(candidate);
				} else if (candidate > high) {
					break;
				}
			}
		}
		vector<int>ans(result.begin(), result.end());
		return ans;
    }
};

int main() {

	int low = 100;
	int high = 300; // 123, 234
    low = 1000, high = 13000;
    Solution s;
	displayvector(s.sequentialDigits(low, high));
	return 0;
}
