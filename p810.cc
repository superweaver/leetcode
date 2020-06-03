#include "common.h"
class Solution {
public:
	bool xorGame(vector<int>& nums) {
        // https://www.cnblogs.com/grandyang/p/9445951.html
		int x = 0;
		int n = nums.size();
		for (auto v : nums) {
			x ^= v;
		}
		// x is xor of all elements
		// if x is 0, return true; Alice wins
		// if x is not zero
		// case 1) n is even
		// in this case, the elements of nums can't be identical
		// if they are all identical, even number of same elements willl result in 0;
		// no matter how many x are in nums, alice will win
		// assume the number of x is odd
		// then alice and bob take turns to remove non-x element until alice remove last non-x element,
		// after bob remove the first x, the lastover are even number of x, the xor of them is zero , alice win
		// assume number of x is even
		//  then alice and bob take turns to remove non-x element until bob remove last non-x element,
		// then alice will face even number of x, alice win
		// so at this moment, alice win if n%2 == 0;
		// case 2) n is odd,
		// bob win;
		return x == 0 || ((n & 1) == 0);
	}
};

int main() {

	Solution s;

	return 0;
}
