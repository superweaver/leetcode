#include "common.h"

class Solution {
public:
    bool rotateString(string A, string B)
    {
        // LCS
        int na = A.size();
        int nb = B.size();
        if (na != nb)
            return false;
        if (A == B) {
            return true;
        }
        vector<vector<int> > dp(na + 1, vector<int>(na + 1, 0));
        // dp[i][j] = the max length of  LCS that ends at A[i] and B[j]
        // dp[i][j] = dp[i-1][j-1] + 1 if A[i] == B[j]
        // otherwisze dp[i][j] = 0;
        int r = 0;
        vector<pair<int, int> > rij;
        for (int i = 1; i <= na; ++i) {
            for (int j = 1; j <= na; ++j) {
                if (A[i - 1] == B[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (r < dp[i][j]) {
                        r = dp[i][j];
                        rij.clear();
                        rij.push_back(make_pair(i, j));
                    } else if (r == dp[i][j]) {
                        rij.push_back(make_pair(i, j));
                    }
                }
            }
        }

        for (auto& p : rij) { 
            // try shift i-j
            int i = p.first;
            int j = p.second;
            if (i == j) {
                if (A == B)
                    return true;
            } else if (i < j) {
                string Bshift = B.substr(j - i) + B.substr(0, j - i);
                if (Bshift == A)
                    return true;
            } else {
                string Ashift = A.substr(i - j) + A.substr(0, i - j);
                if (Ashift == B)
                    return true;
            }
        }
        return false;
    }
};


int main() {

	Solution s;

	return 0;
}
