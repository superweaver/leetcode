#include "common.h"
// https://leetcode.com/problems/check-if-it-is-a-good-array/discuss/419324/Bezout's-Identity
// https://leetcode.com/problems/check-if-it-is-a-good-array/discuss/419368/JavaC%2B%2BPython-Chinese-Remainder-Theorem
//
//The basic idea is that for integers a and b, if gcd(a,b) = d, then there exist integers x and y, s.t a * x + b * y = d;

//This can be generalized for (n >= 2) . e.g. if gcd(a,b,c) = d, then there exist integers x, y, and z, s.t, a* x + b*y + c * z = d.

//Now this problem is just asking if gcd(x1, ......, xn) = 1
// if gcd(x1, x2, ..., xn) == m != 1
// then gcd of any subarry of (x1, x2, ..., xn) is m*k != 1
// then linear combination of any of subarray = 1 won't have integer solution
// then the arrary nums is not a good array

class Solution {

public:
    bool isGoodArray(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0] == 1;
        }
        int a = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (__gcd(a, nums[i]) == 1) return true;
            a = __gcd(a, nums[i]);
        }
        return false;
    }
};


int main() {

    vector<int> nums = {12,5,7,23};
	Solution s;
    cout << s.isGoodArray(nums) << endl;

	return 0;
}
