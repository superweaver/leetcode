#include "common.h"
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int pre_one_len = 0;
        int n = nums.size();
        int result = 0;
        for (int i = 0; i < n;) {
            if (nums[i]) {
                int j = i;
                for (; j < n; ++j) {
                    if(!nums[j])  {
                        break;
                    }
                }
                pre_one_len= j - i; // lenth of ones
                i = j;
                result = max(result, pre_one_len); // in case there is no second ones
            } else {
                // 0
                int j = i;
                for (; j < n; ++j) {
                    if (nums[j]) {
                        break;
                    }
                }
                int len = j - i;
                if (len == 1) {
                    i = j;
                    for(; j < n; ++j) {
                        if (!nums[j]) {
                            break;
                        }
                    }
                    int next_one_len = j - i;
                    result = max(pre_one_len + next_one_len, result);
                    pre_one_len = next_one_len;
                    i = j;
                } else {
                    pre_one_len = 0;
                    i = j;
                }
            }
        }

        if (result == n) { // all ones
            return result - 1;
        }
        return result;
    }
};

int main() {
    vector<int> nums = {1,1,0,1};
    nums = {0,1,1,1,0,1,1,0,1}; // 5
    nums = {1, 1, 1}; // 2
    nums = {1,1,0,0,1,1,1,0,1}; // 4
    nums = {0, 0, 0};

	Solution s;
    cout << s.longestSubarray(nums) << endl;

	return 0;
}
