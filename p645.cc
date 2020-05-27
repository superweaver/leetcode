#include "common.h"
class Solution {
// https://leetcode.com/problems/set-mismatch/discuss/113999/C%2B%2B-True-O(1)-space-O(n)-time-(No-input-modifying)-with-clear-explanation
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int XOR = 0;

        int sum = 0;
        for(int i = 0; i < nums.size(); ++i) {
            XOR ^= nums[i]^(i+1);
            sum += nums[i];
        }
        // XOR == a^b // a != b
        int rsb = XOR&-XOR;// find the right most bit 1

        int x, y;
        x = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            // two categories
            // xor (i+1) again !!!
            if ((i + 1) & rsb) { // nice
                x ^= (i + 1);
            }
            if (nums[i] & rsb) {
                x ^= nums[i];
            }
        }

        y = XOR^x;
        if (x > y) {
            swap(x, y);
        }
        // x < y
        int expect = (1 + nums.size()) * nums.size() / 2;
        if (sum < expect) {
            // x is repeated
            return {x, y};
        } else {
            // y is repeated
            return {y, x};
        }
        // {x,y} or {y, x}
        // it can be determined by summation
         /*
        bool present = false;
        for(int i = 0; i < nums.size(); ++i) {
            if(nums[i] == x) {
                present = true;
            }
        }

        if (!present) {
            swap(x, y);
        }

        return vector<int>{x, y};
        */
    }
};

int main() {

	Solution s;

	return 0;
}
