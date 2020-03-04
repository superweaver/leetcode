#include "common.h"
class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        // 4j+2s = t;
        // j + s = c;
        // 2j + 2(j + s) = t;
        // 2*j = t - 2*c is even
        // j>= 0
        // s = c - j >= 0
        int twoJumbo = tomatoSlices - 2 * cheeseSlices;
        if (twoJumbo >= 0 && twoJumbo %2 == 0){
            twoJumbo >>= 1;
            int small = cheeseSlices - twoJumbo;
            if (small < 0){
                return {};
            }
            return {twoJumbo, small};
        } else {
            return {};
        }
    }
};

int main() {

	Solution s;

	return 0;
}
