#include "common.h"
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 0;
        }
        if (nums[0] > nums[1]) {
            return 0;
        }
        if (nums[n-1] > nums[n-2]) {
            return n-1;
        }

        int low = 1;
        int high = n - 1; // exclude
        while (low < high) {
            int mid = low + (high - low) / 2;
            cout << mid << endl;
            if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1]) {
                return mid;
            } else if (nums[mid - 1] > nums[mid] && nums[mid] > nums[mid + 1]) {
                high = mid;
            } else if (nums[mid - 1] < nums[mid] && nums[mid] < nums[mid + 1]) {
                low = mid + 1;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};

int main() {
    vector<int> nums = {1, 2, 1, 3, 5, 6, 4};
    nums = {3,2,1};

    Solution s;
    cout << s.findPeakElement(nums) << endl;

	return 0;
}
