#include "common.h"
// https://buptwc.com/2018/05/22/Leetcode-837-New-21-Game/
// https://www.cnblogs.com/grandyang/p/10386525.html
class Solution {
  public:
    double new21Game(int N, int K, int W) {
        if (K == 0 || N >= K + W) {
            return 1;
        }
        vector<double> dp(N + 1, 0);
        dp[0] = 1;
        // p[i] is the probablity of get point i
        // p(i) = sum(p(i-m) * p(pick== m));
        // p(i) = 1/W * sum(p(i-1)+....p(i-W))
        double psum = 1; // use psum as sum(p(i-1)+....p(i-W)) , note i - W >= 0
        for (int i = 1; i <= N; ++i) {
            dp[i] = psum / W;   // use psum as sum(p(i-1)+....p(i-W)) , note i - W >= 0
            if (i < K) {
                psum += dp[i]; // keep drawing
            } else {
                // stop drawing
            }
            // note psum  need to exclude previous leftmost dp
            // if (i >= W && i < K + W) {
            if (i >= W) {
                psum -= dp[i - W];
            }
        }
        double r = 0;
        for (int i = K; i <= N; ++i) {
            r += dp[i];
        }
        return r;
    }
};

int main() {

    Solution s;

    return 0;
}
