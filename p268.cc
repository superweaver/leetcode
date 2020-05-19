#include "common.h"
// https://leetcode.com/problems/missing-number/discuss/69786/3-different-ideas%3A-XOR-SUM-Binary-Search.-Java-code
//
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        //1) xor
        int n = nums.size();
        int result = n; // initial value is important
        for (int i = 0; i < n; ++i) {
            result ^= i;
            result ^= nums[i];
        }
        // why it works
        // result = n intially, and result ^ i = 0, 1, ... n-1
        // so it covers 0...n
        // then result ^ nums[i],
        // after all operations, only the missing one is left
        return result;
    }
    // 2) sum + x = n * (n+1) /2
    // x = n *(n+1)/2 - summation
    //
    // 3) binary search if nums is sorted
};

int main() {

    vector<int> nums = {0, 2, 3};


	Solution s;
    cout << s.missingNumber(nums) << endl;

	return 0;
}
