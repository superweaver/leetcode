#include "common.h"
// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/discuss/103062/C%2B%2B-Clean-Code-2-Solution-Sort-O(NlgN)-and-max-min-vectors-O(N)

/*
 *
    From the left, for a number to stay untouched, there need to be no number less than it on the right hand side;
    From the right, for a number to stay untouched, there need to be no number greater than it on the left hand side;

Those 2 can be easily checked if we build 2 vectors:

    max so far from the left,
    and min so far from the right;

 * */

class Solution {
  public:
    int findUnsortedSubarray(vector<int> &nums) {
        int n = nums.size();
        vector<int> maxlhs(n); // max number from left to cur
        vector<int> minrhs(n); // min number from right to cur
        for (int i = n - 1, minr = INT_MAX; i >= 0; i--) {
            minrhs[i] = minr = min(minr, nums[i]);
        }
        for (int i = 0, maxl = INT_MIN; i < n; i++) {
            maxlhs[i] = maxl = max(maxl, nums[i]);
        }

        int i = 0, j = n - 1;
        while (i < n && nums[i] <= minrhs[i]) {
            i++;
        }
        while (j > i && nums[j] >= maxlhs[j]) {
            j--;
        }
        return j + 1 - i;
    }
};
int main() {

    Solution s;

	return 0;
}
