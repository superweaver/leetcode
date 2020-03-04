#include "common.h"
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
		int n = nums.size();
		sort(nums.begin(), nums.end());
		/*
		int total = accumulate(nums.begin(), nums.end(), 0);
		if(total <= threshold) {
			return 1;
		}
		*/
		if (n == threshold) {
			return nums.back();
		}
		int low = 1;
		int high = nums.back();
		while(low < high) {
			int mid = low + (high - low) / 2;
			int sum = 0;
			auto pre = nums.begin();
            for (int i =  mid, k = 1; ; ) {
				auto it = upper_bound(pre, nums.end(), i);
				sum += k * distance(pre, it);
				pre = it;
				if (i > nums.back()) {
					break;
				}
                i += mid;
                k++;
            }
			if (sum > threshold) {
				low = mid + 1;
			} else {
				high = mid;
			}
        }
		return low;
    }
};

int main() {
    vector<int> nums = { 1, 2, 5, 9 };
    int threshold = 6; // 5
	nums = {2,3,5,7,11}, threshold = 11; // 3
	nums = {19}, threshold = 5; // 4

    Solution s;
	cout << s.smallestDivisor(nums, threshold) << endl;
	return 0;
}
