#include "common.h"
class Solution {
public:
    int minFlips(int a, int b, int c) {
        int t = a | b;
		int diff = t^c;
		int step = 0;
		while(diff) {
			int lowerbit = diff & -diff;
            if (lowerbit & c) {  // bit in c is 1 // bit in a and b are 0
				step++;
            } else {  // bit in c is 0, bits in a and b has at least one bit 1
				if (a & lowerbit) {
					step++;
				} 
				if (b & lowerbit) {
					step++;
				}
			}
            diff &= (diff - 1);
        }
		return step;
    }
};

int main() {
	int a = 2; 
	int b = 6;
	int c = 5; // 3
	a = 4, b = 2, c = 7; // 1

	Solution s;
	cout << s.minFlips(a, b, c) << endl;

	return 0;
}
