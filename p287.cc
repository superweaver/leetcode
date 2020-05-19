#include "common.h"
class Solution {
public:
    //  math makes perfect !
    //  http://keithschwarz.com/interesting/code/find-duplicate/FindDuplicate.python
    int findDuplicate(vector<int> nums) {
        int n = nums.size();
        if (n > 1) {
            int x_0 = n;
            int slow = nums[x_0 - 1];
            int fast = nums[nums[x_0 - 1] - 1];
            while (slow != fast) {
                slow = nums[slow - 1];
                fast = nums[nums[fast - 1] - 1];
            }
            int finder = x_0;
            while (finder != slow) {
                slow = nums[slow - 1];
                finder = nums[finder - 1];
            }
            return slow;
        }

    }

};


int main() {

	Solution s;

	return 0;
}
