#include "common.h"
// similar to 3sum
// explanation 
// https://leetcode.com/problems/valid-triangle-number/discuss/128135/A-similar-O(n2)-solution-to-3-Sum
// for any nums[k], if nums[i] + nums[j] > nums[k], then there are j-i pairs nums[i'] + nums[j] > nums[k]
// where i' = [i, ..., j-1]
class Solution {
  public:
    int triangleNumber(vector<int> &nums) {
        sort(nums.begin(), nums.end(), less<int>());
        int result = 0;
        int size = nums.size();
        for (int i = size - 1; i > 1; i--) {
            int l = 0, r = i - 1;
            while (l < r) {
                if ((nums[l] + nums[r]) > nums[i]) {
                    // summation of nums[l...r-1] and nums[r] are > nums[i]
                    result += (r - l);
                    r--;
                } else {
                    l++;
                }
            }
        }
        return result;
    }
};

int main() {

    Solution s;

    return 0;
}
