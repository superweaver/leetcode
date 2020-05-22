#include "common.h"
// not solved

// http://www.cnblogs.com/grandyang/p/6057934.html
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A)
    {
        int n = A.size();
        int result = 0;
        vector<unordered_map<int, int> > dp(n);
        // dp[i] is hashmap <diff, count>
        // dp[i][diff] is the count of generalized arithmetic slice (length two)
        // ending at i, with difference of diff
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                long diff = (long)A[i] - A[j]; // fuck it, convert it to long before substraction
                if (diff > INT_MAX || diff < INT_MIN) {
                    continue;
                }
                int delta = (int)diff;
                dp[i][delta]++;  // note : A[j] and A[i] forms a new generalized arithmetic slice
                if (dp[j].count(delta)) {
                    // then add A[i] to then end of previous generalized arithmetic slice
                    // forms a true arithmetic slice
                    result += dp[j][delta];
                    dp[i][delta] += dp[j][delta];  // add previous generalized arithmetic slice
                }
            }
        }
        return result;
    }
};


int main() {

	Solution s;

	return 0;
}
