#include "common.h"
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        // dp and reuse A
        int n = A.size();
        if (n == 1) {
            return A[0][0];
        }
        int result = INT_MAX;
        for(int i = 1; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                int pre = INT_MAX;
                for(int k = -1; k < 2; ++k) {
                    if (j +k >= 0 && j + k <n) {
                        pre = min(pre, A[i - 1][j + k]);
                    }
                }
                A[i][j] += pre;
                if(i == n-1) {
                    result = min(result, A[i][j]);
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
