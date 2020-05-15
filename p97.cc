#include "common.h"
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int M = s1.size();
        int N = s2.size();
        int N3 = s3.size();
        if (N3 != (M + N)) {
            return false;
        }
        if (M == 0) {
            return s2 == s3;
        }
        if (N == 0) {
            return s1 == s3;
        }

        // dp
        // f[i][j] == true means s1[0, i) s2[0, j) matches s3[0, i+j)
        // f[i][j] = (s1[i-1] == s3[i+j-1] && f[i-1][j]) || (s2[j-1] == s3[i+j-1] && f[i][j-1])
        // return f[M][N]
        // f[i][j] is determained by f[i-1][j] and f[i][j-1]
        vector<vector<bool>> f(M + 1, vector<bool>(N + 1, false));
        int i = 0, j = 0;
        // first row, s2
        f[0][0] = true;
        i = 0;
        for (j = 1; j <= N; j++) {
            f[i][j] = f[i][j - 1] && s2[j - 1] == s3[i + j - 1];
        }
        // first column, s1
        j = 0;
        for (i = 1; i <= M; i++) {
            f[i][j] = f[i - 1][j] && s1[i - 1] == s3[i + j - 1];
        }

        for (i = 1; i <= M; i++) {
            for (j = 1; j <= N; j++) {
                f[i][j] = (f[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                          (f[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
       return f[M][N];

    }
};

int main() {

	Solution s;

	return 0;
}
