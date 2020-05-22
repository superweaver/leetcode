#include "common.h"
// https://leetcode.com/problems/minimum-moves-to-equal-array-elements/discuss/93817/It-is-a-math-question
class Solution {
  public:
    int minMoves(vector<int> &nums) {
        /*
    int n = nums.size();
    if (n == 0) {
        return 0;
    }
    int step = 0;
    sort(nums.begin(), nums.end());
    int i = 0;
    int last = nums[i];
    for (i = 1; i < n; ++i) {
        int prev = step;
        step = step + (nums[i] + step - last);
        last = nums[i] + prev;
    }*/
        // last[i] = nums[i] + F[i-1];
        // F[i] = F[i-1] + (nums[i] + F[i-1] - last[i-1])
        // so F[i] - F[i-1] = F[i-1] - F[i-2] + (nums[i] - nums[i-1])
        // so F[i] - F[i-1] = nums[i] - nums[0]
        // so F[i] = sum (nums[0..i]) - (i-0+1)*nums[0];
        // step = sum of nums - n * min(nums);
        int minElement = INT_MAX;
        long sum = 0;
        for (auto i : nums) {
            sum += i;
            minElement = min(minElement, i);
        }
        return sum - minElement * nums.size();
    }
};

int main() {

	Solution s;

	return 0;
}
