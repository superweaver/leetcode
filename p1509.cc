#include "common.h"
// https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/discuss/730567/JavaC%2B%2BPython-Straight-Forward
class Solution {
public:
    int minDifference(vector<int>& nums) {
        // Given an array nums, you are allowed to choose one element of nums and change it by any value in one move.
        // this is equivalent to remove three elements
        // 1 <= nums.length <= 10^5
        int n = nums.size();
        if (n <= 3) {
            return 0;
        }
        sort(nums.begin(), nums.end());
        // four cases
        // (1) remove biggest 3 
        // (2) remove biggest 2, and smallest 1
        // (3) remove biggest 1, and smallest 2
        // (4) remove smallest 3
       // min(nums[n - 4] - nums[0], nums[n - 3] - nums[1], nums[n - 2] - nums[2],
       //     nums[n - 1] - num[3]);
       int result = INT_MAX;
       for (int i = 0; i <4; ++i) {
           result = min(result, nums[n - 4 + i] - nums[i]);
       }
       return result;
    }
};

int main() {

	Solution s;

	return 0;
}
