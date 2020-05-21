#include "common.h"
// https://leetcode.com/problems/lexicographical-numbers/discuss/86237/AC-200ms-c%2B%2B-solution-beats-98
// nice explanation
// https://leetcode.com/problems/lexicographical-numbers/discuss/86231/Simple-Java-DFS-Solution
// https://leetcode.com/problems/lexicographical-numbers/discuss/86242/Java-O(n)-time-O(1)-space-iterative-solution-130ms

class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res(n);
        int cur = 1; // current smallest element
        for (int i = 0; i < n; i++) {
            res[i] = cur;   // just assign
            // prepare for next one
            if (cur * 10 <= n) {
                // if cur * 10 <= n
                // then cur * 10 must be next lexical smallest one
                cur *= 10;
            } else {
                // cur * 10 > n
                // need to increase second least significant number
                //
                // if (cur == n) then cur + 1 must >= n
                // in that way, need to divide it by 10
                if (cur == n) {
                    cur /= 10;
                }
                cur += 1;
                while (cur % 10 == 0) { // remove trailing 0
                    cur /= 10;
                }
            }
        }
        return res;
    }
};

int main() {

	Solution s;

	return 0;
}
