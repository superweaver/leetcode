#include "common.h"
class Solution {
  public:
    int maxValueAfterReverse(vector<int> &nums) {
        //https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/discuss/490652/concise-C%2B%2B-O(N)-40ms-beats-100-(-maxmin-minmax-)
        // https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/discuss/489882/O(n)-Solution-with-explanation
        // 
        // case 1) reverse [0...i], i > 0, this is equivalent to reverse [i+1, n-1]
        // case 2) reverse [i...j], Only when max(nums[i], nums[i -1]) < min(nums[j], nums[j-1]) or vice versa, will reverse subarray between i and j lead to increased sum
        // And if exchanged, the candidate result = all + 2 * (difference of the above 2 values);
        //
       int all = 0; // no reverse
       int minmax = INT_MAX;
       int maxmin = INT_MIN;
       int inc = 0; // for case 1
       int n = nums.size();
       for (int i = 1; i < n; ++i) {
           int temp = abs(nums[i]-nums[i-1]);
           all += temp;
           // case 2
           minmax = min(minmax, max(nums[i], nums[i-1]));
           maxmin = max(maxmin, min(nums[i], nums[i-1]));
           // case 1
           inc = max(inc, abs(nums[0]-nums[i]) - temp);
       }
       return all + max(inc, 2 * (maxmin-minmax));
    }
};

int main() {

	Solution s;
	return 0;
}
