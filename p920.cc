#include "common.h"
//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-920-number-of-music-playlists/
// Author: Huahua
class Solution_hua {
public:
  int numMusicPlaylists(int N, int L, int K) {
    constexpr long kMod = 1e9 + 7;
    // K doesn't change
    // dp[i][j] := # of playlists of length i using j different songs.
    vector<vector<long>> dp(L + 1, vector<long>(N + 1, 0));
    dp[0][0] = 1; // empty set
    for (int i = 1; i <= L; ++i) { // length of list
        int upper = min(i, N);     // for a list of length i, there are at most i different songs
                                   // and there are only N songs in total
                                   // so upper = min(i, N);
        for (int j = 1; j <= upper; ++j) {
            dp[i][j] = (dp[i - 1][j - 1] * (N - (j - 1))  // adding a new song to the end of list,
                                                          // there are N-(j-1) songs are unused
                        + dp[i - 1][j] * max(j - K, 0)) % // reuse previous songs
                       kMod;
        }
    }
    return dp[L][N];
  }
};

class Solution {
    // https://www.cnblogs.com/lz87/p/11651570.html
    // https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-920-number-of-music-playlists/
    // https://buptwc.com/2018/10/08/Leetcode-920-Number-of-Music-Playlists/

  public:
    int numMusicPlaylists(int N, int L, int K) {
        // dp
        // dp[N][L][K]
        // consider the last song, there are two possibilities
        // 1)the last song doesn't appear in the previous list of length L-1
        // 2)the last song appears in the previous list of length L-1, but the last (K + 1) (
        // include the last) must not have duplication case 1) has dp[N-1][L-1][K] * N; we have N
        // choices of last song case 2) has dp[N][L-1][K] * (N-K); in the last (K + 1) songs, the
        // last song can't be its previous K songs so there are totally N - K (has appeared songs)
        // base case N==1, return 1;
        // if (N==K+1), return N!
        // if (N==L), return N!
        vector<vector<long>> dp(N + 1, vector<long>(L + 1, 0));
        vector<long> factorial(N + 1, 0);
        factorial[0] = 1;
        for (int i = 1; i <= N; ++i) {
            factorial[i] = (factorial[i - 1] * i) % Mod;
        }
        return (int)helper(N, L, K, dp, factorial);
    }

  private:
    const int Mod = 1000000007;
    long helper(int n, int l, int k, vector<vector<long>> &dp, vector<long> &factorial) {
        if (dp[n][l] > 0) {
            return dp[n][l];
        }
        if (n == k + 1 || n == l) {
            return dp[n][l] = factorial[n];
        } else {
            return dp[n][l] = (helper(n - 1, l - 1, k, dp, factorial) * n +
                               helper(n, l - 1, k, dp, factorial) * (n - k)) %
                              Mod;
        }
    }
};

int main() {
    Solution s;
    int N = 2, L = 3, K = 0;
    cout << s.numMusicPlaylists(N, L, K) << endl;
    return 0;
}
