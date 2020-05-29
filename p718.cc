#include "common.h"
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        if (A.empty() || B.empty()) {
            return 0;
        }
        int m = A.size();
        int n = B.size();
        // dp[i][j] is the max lenght of continuous subarray ending at A[i] and B[j]
        // dp[i][j] = 0 if A[i] != B[j]
        // dp[i][j] = dp[i-1][j-1] + 1 ;  if A[i] == B[j]
        // dp[0][0] = A[0] == B[0] ? 1 : 0;
        // shift by 1
        int result = 0;
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(A[i] == B[j]) {
                    dp[i+1][j+1] = dp[i][j] + 1;
                    result = max(result, dp[i+1][j+1]);
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
