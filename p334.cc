#include "common.h"
class Solution_my {
public:
	bool increasingTriplet(vector<int>& nums) {
		int n = nums.size();
		if (n < 3) return false;
		int imin = 0;
		int ia = 0;
		int ib = -1;
		//int ic = -2;
		for (int i = 1; i < n; ++i) {
			if (ia < ib) {
				if (nums[i] > nums[ib]) {
					return true;
				}
				else if(nums[i] == nums[ib]) {
					ib = i;
				} else {
					// nums[i] < nums[ib]
					if (nums[i] > nums[imin]) {
						ia = imin;
						ib = i;
					} else {
						if (nums[i] > nums[ia]) {
							ib = i;
						} else if (nums[i] == nums[ia]) {
							// do nothing
						}
						else {
							// nums[i] < nums[ia]
						}
					}
				}
            } else { // ia > ib
                // ib won't be same as ia
                if (nums[i] > nums[ia]) {
					ib = i;
				}
				else {
					ia = i;
				}
            }

            if (nums[i] < nums[imin]) {
				imin = i;
			}
		}
		return false;
	}
};
class Solution {
    bool increasingTriplet(vector<int> &nums) {
        int c1 = INT_MAX, c2 = INT_MAX;
        // maintain an increasing array
        for (int x : nums) {
            if (x <= c1) {
                c1 = x;           // c1 is min seen so far (it's a candidate for 1st element)
            } else if (x <= c2) { // here when x > c1, i.e. x might be either c2 or c3
                c2 = x;           // x is better than the current c2, store it
            } else {              // here when we have/had c1 < c2 already and x > c2
                return true;      // the increasing subsequence of 3 elements exists
            }
        }
        return false;
    }
};

int main() {

	Solution s;

	return 0;
}
