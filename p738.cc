#include "common.h"

class Solution {
  public:
    int monotoneIncreasingDigits(int N) {
        if (N < 10) {
            return N;
        }
        int n = N;
        vector<int> vn;
        while (n) {
            vn.push_back(n % 10);
            n /= 10;
        }
        n = vn.size();
        // find first digit which is smaller than its left digit
        // we need to make its left digit smaller :)
        int i = n - 2;
        for (; i >= 0; --i) {
            if (vn[i] < vn[i + 1]) {
                break;
            }
        }
        if (i == -1) {
            return N;
        }

        // key
        // 33332
        // -> 29999
        ++i;
        for (; i + 1 < n;) { // boundary
            // key point here
            if (vn[i + 1] == vn[i]) {
                ++i;
            } else {
                break;
            }
        }
        int result = 0;
        for (int j = n - 1; j >= i; --j) {
            result = result * 10 + vn[j];
        }
        result *= (int)pow(10, i);
        --result; // :)
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
