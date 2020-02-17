#include "common.h"
class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
		// counting?
		int n = nums.size();
		if (n == 1) {
			return 0;
		}
		// up down up down
		int r1 = 0;
		for (int j = 1; j < n; j += 2) {
			int neighbor = nums[j-1];
			if (j + 1 < n) {
				neighbor = min(neighbor, nums[j+1]);
			}
			if (nums[j] >= neighbor) {
				r1 += nums[j] - neighbor  + 1;
			}
		}
		// down up down up
		int r2 = 0;
		for (int j = 0; j < n; j+=2) {
			int neighbor = INT_MAX;
			if (j - 1 >= 0) {
				neighbor = min(neighbor, nums[j-1]);
			}
			if (j + 1 < n) {
				neighbor = min(neighbor, nums[j+1]);
			}
            if (nums[j] >= neighbor) {
                r2 += nums[j] - neighbor + 1;
            }
        }
		return min(r1, r2);
    }
};

int main() {

	vector<int> nums = {1, 2, 3}; // 2
	nums = {9,6,1,6,2}; // 4
	nums = {10,4,4,10,10,6,2,3}; // 13
	Solution s;
	cout << s.movesToMakeZigzag(nums) << endl;

	return 0;
}
