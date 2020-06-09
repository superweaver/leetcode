#include "common.h"
class Solution {
public:
    int minFlipsMonoIncr(string S) {
        // dp[i][0] is min number of flip to make S[0...i] monotone increasing and at last S[i] = 0;
        // dp[i][1] is min number of flip to make S[0...i] monotone increasing and at last S[i] = 1;
        int v0 = (S[0]=='1');
        int v1 = (S[0]=='0');
        int ones = S[0]-'0';
        for(size_t i = 1; i < S.size(); ++i){
            if(S[i] == '0') {
                v1 = min(v0 + 1, v1 + 1);
                v0 = ones;
            } else{
                ones++;
                v1 = min(v0, v1);
                v0 = ones;
            }
        }
        return min(v0, v1);
    }
};

int main() {

	Solution s;

	return 0;
}
