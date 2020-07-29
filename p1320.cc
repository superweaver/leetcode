#include "common.h"
#include <functional>
// https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-1320-minimum-distance-to-type-a-word-using-two-fingers/
class Solution_3d {
public:
    int minimumDistance(string word) {
        // O(27^2*n)
        //
        // dp[i][l][r] is the minium distance to go through substring word[i...n]
        // while currently left finger is at char l and right finger i at char r
        //
        // use char 26 to represent a un-used finger
        //
        // assume 
        // char c = word[i];
        // dp[i][l][r] = min(dp[i+1][c][r] + cost(l, c) // use left finger
        //                   dp[i+1][l][c] + cost(r, c));// use right ringer
        // if (i >= n) return 0;
        // return dp[0][26][26]
        int n = word.size();
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(27, vector<int>(27, -1))); // not calculated
        auto cost = [](int c1, int c2) {
            if (c1 == 26) {
                return 0;
            }
            return abs(c1 / 6 - c2 / 6) + abs(c1 % 6 - c2 % 6);
        };

        function<int(int, int, int)> helper = [&](int i, int l, int r) {
            if (i >= n) {
                return 0;
            }
            if (dp[i][l][r] >= 0) {
                return dp[i][l][r];
            }
            int c = word[i] - 'A';
            return dp[i][l][r] =
                       min(cost(l, c) + helper(i + 1, c, r), cost(r, c) + helper(i + 1, l, c));
        };
        return helper(0, 26, 26);
    }
};

class Solution_2d {
public:
    int minimumDistance(string word) {
        // similar idea for 3d
        // observation
        // dp[i][o] means the minimum distance needed for finish substring word[i..n] 
        // when one finger is at i-1, while the other one is at o
        // return dp[0][26]
        // O(27*n)
        constexpr int FreeChar = 26;
        int n = word.size();
        vector<vector<int>> dp(n, vector<int>(27, -1)); // not calculated

        auto cost = [](int c1, int c2) {
            if (c1 == FreeChar) {
                return 0;
            }
            return abs(c1 / 6 - c2 / 6) + abs(c1 % 6 - c2 % 6);
        };

        function<int(int, int)> helper = [&](int i, int o) {
            if (i >= n) {
                return 0;
            }
            if (dp[i][o] >= 0) {
                return dp[i][o];
            }
            int pre = (i >= 1) ? (word[i - 1] - 'A') : FreeChar;
            int c = word[i] - 'A';
            return dp[i][o] = min(
                       cost(pre, c) + helper(i + 1, o), // use pre to c, then the other is still o
                       cost(o, c) + helper(i + 1, pre)  // use o to c, then the other is pre
                   );
        };
        return helper(0, FreeChar);
    }
};

class Solution {
    // bottom up
  public:
    int minimumDistance(string word) {
        int n = word.size();
        constexpr int FreeChar = 26;
        // INT_MAX/2
        vector<vector<int>> dp(n + 1, vector<int>(27, INT_MAX / 2));
        // dp[i][j] is the minimum distance to print substring [0..i)
        // and one finger is pointing to char word[i-1], while the other finger is pointing to
        // char j
        
        // base case
        dp[0][FreeChar] = 0;
        auto cost = [](int c1, int c2) {
            if (c1 == FreeChar) {
                return 0;
            }
            return abs(c1 / 6 - c2 / 6) + abs(c1 % 6 - c2 % 6);
        };
        for (int i = 0; i < n; ++i) {
            int pre = (i >= 1) ? word[i - 1] - 'A' : FreeChar;
            int c = word[i] - 'A';
            for (int j = 0; j <= 26; ++j) {
                dp[i+1][j] = min(dp[i+1][j], dp[i][j] + cost(pre, c)); // j is the other, move pre
                dp[i + 1][pre] =
                    min(dp[i + 1][pre], dp[i][j] + cost(j, c)); // pre is the other, move j
            }
        }
        return *min_element(dp[n].begin(), dp[n].end());
    }
};



int main() {
    string word = "CAKE"; // 3
	word = "HAPPYY";
//	word = "HAP";
    {
        Solution_3d s;
        cout << s.minimumDistance(word) << endl;
    }
    {
        Solution_2d s;
        cout << s.minimumDistance(word) << endl;
    }
    {
        Solution s;
        cout << s.minimumDistance(word) << endl;
    }

    return 0;
}
