#include "common.h"

class Solution {
public:
    int findIntegers(int num) {
        // 1 <= num <= 10^9
        int n = getN(num);
        if (n == 0) return 1;
        //vector<int> LDP(n + 1, 0); // local, the number of combinations of length n, whose leading digit is 1
        int N = max(n, 20);
        vector<int> GDP(N + 1, 0);  // global,the number of combinations of length n
        // GDP[n] = LDP(n) + GDP[n-1] // append any GDP[n-1] by '0] is good
        // LDP[n] = GDP[n-2]      // append any GDP[n-2] by '01' is LDP[n]
        // GDP[n] = GDP[n-1] + GDP[n-2]
        // GDP[0] = 1, empty, one way
        // GDP[1] = 2; 0 or 1
        // GDP[2] = 3; 00, 01, 10
        // GDP[3] = 5; 000, 001, 010, 100, 101
        GDP[0] = 1;
        GDP[1] = 2;
        //GDP[2] = 3;
        for (int i = 2; i <= N; ++i) {
            GDP[i] = GDP[i - 1] + GDP[i - 2];
        }
        int r = 0;
        int pre = n;
        bool hasConsecutiveOne = false;
        r++;  // the zero
        for (int i = n; i >= 1; --i) {
            if (num & (1 << (i - 1))) {
                if (!hasConsecutiveOne) {
                    r += (GDP[i - 1] - 1); // G[len-1] without zero
                    r++;                   // get # for n upto xxx10000
                    if (pre == i + 1) {    // current i and pre are both one
                        --r;               // remove it
                                           // no need to continue loop, since all the following data
                                           // have pattern with xxx11xxxx upto num
                        hasConsecutiveOne = true;
                        break;
                    }
                }
                pre = i;
            }
        }
        return r;
    }
private:
    int getN(int num) {
        int n = 0;
        while(num) {
            n++;
            num >>= 1;
        }
        return n;
    }
};


int main() {

	Solution s;

	return 0;
}
