#include "common.h"
class Solution {
public:
    int flipLights(int n, int m) {
        //https://www.cnblogs.com/grandyang/p/7595595.html
        // every operation has same effect for i and 6 + i th bulb
        // the pattern has repetition
        // so n = n%6; if(n == 0) n = 6;
        if(n == 0 || m == 0) return 1;
        // n > 0, m > 0
        if(n==1) return 2;
        if(n==2) return m > 1 ? 4 : 3;
        // if n == 2, m = 1, there is 00, 10, 01
        // if m = 2, then 11 can be achieved.
        // n >= 3
        // n == 3, 000, 101, 010, 100 can be achieved.
        // for n > 3, there are also only 4 states
        if (m==1) return 4;
        // for m >= 2, considering 3
        // if m == 2, 001, 110, 011 can be aheived
        // if m > 2, 111 can be achieved.
        return m == 2 ? 7 : 8;

        // why do we consider only first three bits?


    }
};

int main() {

	Solution s;

	return 0;
}
