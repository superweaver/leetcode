#include "common.h"
class Solution {
public:
	bool isOneBitCharacter(vector<int>& bits) {
		int n = bits.size();
		int j = n - 2;
        // starting from j = n - 2 and going backwards, bits[n-1] == 0
        // count the length of 1
        // if (len&1) , len is odd, the last 0 must be combined with this extra 1
        // if (len is even), then the last 0 must be a single 0
		int ones = 0;
		for (; j >= 0; --j) {
			if (bits[j] == 1) {
				ones++;
			}
			else {
				break;
			}
		}

		if ((ones & 1) == 1) {
			return false;
		}
		else {
			return true;
		}
	}
};

int main() {

	Solution s;

	return 0;
}
