#include "common.h"

class Solution {
public:
    int majorityElement(vector<int>& nums) {

        // 1) quick select
        // 2) Boyer-Moore Voting Algorithm
        size_t n = nums.size();
        int count = 1;
        int candidate = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (count == 0) {
                candidate = nums[i];
                count = 1;
            } else {
                if (candidate == nums[i]) {
                    ++count;
                } else {
                    --count;
                }
            }
        }
        return candidate;
    }
};



int main() {

	Solution s;

	return 0;
}
