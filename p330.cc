#include "common.h"
//https://leetcode.com/problems/patching-array/discuss/78488/Solution-%2B-explanation
class Solution {
  public:
    int minPatches(vector<int> &nums, int n) {
        long miss = 1; // missing is (upperbound + 1) using currently available nums[0..i]
        int added = 0;
        size_t i = 0;
        while (miss <= n) {
            if (i < nums.size() && nums[i] <= miss) {
                miss += nums[i]; // the covering range can be extended now; miss will be new upperbound + 1
                i++;
            } else {
                added++; // add this miss to vector
                miss += miss; // and check next missing
            }
        }
        return added;
    }
};

int main() {

    Solution s;

    return 0;
}
