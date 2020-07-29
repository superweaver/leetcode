#include "common.h"
class Solution {
public:
    int numWays(int steps, int arrLen) {
        // input = [1; 0; 0...;0]
        // transform matrix
        // T = [1, 0,.... 0;
        //      1, 1, ... 0;
        //      0, 1, 1... 0;
        //      0, 1, 1... 0;
        //      0
        //      ..
        //
        //
        //
        //      ..........1, 0;
        //      ..........1, 1;
        //      ..........1, 1;]
        //     output = input*T^steps

        //int N = arrLen + 2;
        const long Mod = 1e9 + 7;
        //vector<long> count(N, 0);

        int UpperBound = min(steps - 0 + 1, arrLen) + 2;

        vector<long> count(UpperBound, 0);
        count[1] = 1;
        for (int i = 0; i < steps; ++i) {
            vector<long> next(UpperBound, 0);
            // ideally, arrlen should be used
            // but we only care about cout[1];
            // so at most position upper can impact count[1]
            int upper = min(steps - i + 1, arrLen);
            for (int j = 1; j <= upper; ++j) {
                next[j] = (count[j-1] + count[j] + count[j+1]) % Mod;
            }
            next.swap(count);
        }
        return count[1];
    }
};

int main() {
    int steps = 2, arrLen = 4; // 2
    steps = 4, arrLen = 2; // 8;
    steps = 434, arrLen = 291270;

    Solution s;
    cout << s.numWays(steps, arrLen) << endl;

	return 0;
}
