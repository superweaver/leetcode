#include "common.h"

class Solution {
public:
    typedef unsigned long long ULL;
    int checkRecord(int n) {
        // dp[i] = A[i] + NA[i]
        // A means has one A
        // NA means has no A
        // /* this is wrong;
        // A[i] = any of sequance of NA[i-1] and then insert A at one of (i+1) slots
        // there are i +1 slots to insert A
        // A[i] = i * NA[i-1];
        // A[i] is more than that;
        // example, LLL is not good for N[3] but insert A inside is OK for N[4], LLAL
        // */
        // for a sequency of A[i], it must be composed by NA[k] A NA[i-k-1], k = [0..i-1]
        // then A[i] = sum (NA[k] * NA[i-k-1]) ;
        // for NA
        // NA[i] = a + b
        // a = NA[i-1] by appending P at i
        // b = NA[i-1] - NA[i-4] by appending L at i
        // for any sequence in NA[i-4] , adding "PLL", then it is a good one for a length of i-1
        // record
        // but we can't add L any more
        //
        // NA[i] = 2NA[i-1] - NA[i-4]
        // NA[-1] = 1; "LL" + L
        // NA[0] =  1
        // NA[1] =  2 (L or P)
        // NA[2] =  4 (LL, LP, PL, PP)
        // NA[3] =  7 (LL, LP, PL, PP) + P and  (LL, LP, PL, PP)+L but remove LLL
        // NA[4] = 2*NA[3] -N[0] = 14-1 = 13
        // dp[0] = 1
        // dp[1] = 3
        // dp[2] = 8
        // dp[3] = 19
        // here b = NA[2] - "LL" = 3
        if (n < 0) return 0;
        if (n == 0) return 1;
        if (n == 1) return 3;
        if (n == 2) return 8;
        if (n == 3) {
            return 19;
        }
        vector<ULL> NA(n + 1, 0);
        NA[0] = 1;
        NA[1] = 2;
        NA[2] = 4;
        NA[3] = 7;
        const ULL prime = 1e9 + 7;
        for (int len = 4; len <= n; ++len) {
            // NA[len] = 2 * NA[len - 1] - NA[len - 4];
            NA[len] = NA[len-1];
            NA[len] %= prime;
            // NA[len-1] may have been moduloed
            // only two options
            if (NA[len - 1] >= NA[len - 4]) {
                NA[len] += (NA[len - 1] - NA[len - 4]) % prime;
            } else {
                // multiple primes // tricky
                NA[len] += prime - (NA[len - 4] - NA[len - 1]) % prime;
            }
            NA[len] %= prime;
        }

        ULL A = 0;
        for (int len = 0; len < n; ++len) {
            // len = left length
            // won't cause overflow
            A += (NA[len] * NA[n - 1 - len]) % prime;
            A %= prime;
        }
        ULL result = A + NA[n];
        result %= prime;
        return result;
    }
};


int main() {

	Solution s;

	return 0;
}
