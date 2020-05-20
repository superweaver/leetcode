#include "common.h"
//https://leetcode.com/problems/wiggle-sort-ii/discuss/77682/Step-by-step-explanation-of-index-mapping-in-Java
//https://leetcode.com/problems/wiggle-sort-ii/discuss/77681/O(n)-time-O(1)-space-solution-with-detail-explanations
//
class Solution {
public:
	void wiggleSort(vector<int>& nums) {
		if (nums.empty()) {
			return;
		}
		int n = nums.size();

		// Step 1: Find the median using nth_element or quick_select
		vector<int>::iterator nth = next(nums.begin(), n / 2);
		nth_element(nums.begin(), nth, nums.end());
		int median = *nth;

		// Step 2: Tripartie partition within O(n)-time & O(1)-space.
		auto m = [n](int idx) { return (2 * idx + 1) % (n | 1); };
        // (n|1) is to find the nearest odd that is not less than n.
        int first = 0, mid = 0, last = n - 1;
		while (mid <= last) {
			if (nums[m(mid)] > median) {
                // larger than median, then put them to odd slots from head
                swap(nums[m(first)], nums[m(mid)]);
				++first;
				++mid;
			}
			else if (nums[m(mid)] < median) {
                // smaller tan median, put them to even slots from tail
				swap(nums[m(mid)], nums[m(last)]);
				--last;
			}
			else {
				++mid;
			}
		}
	}
};

int main() {

	Solution s;

	return 0;
}
