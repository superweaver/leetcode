#include "common.h"

class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        // The knight continues moving until it has made exactly K moves or has moved off the chessboard.
        // fuck it.
        // If it is off the chessboard, it won't continues.
        // dp[x][y][k] is the probability of knight locating at x, y after k moves, x,y still in chessboard.
        // then do next move, uniformly in 8 direction
        if(K == 0) return 1;
        //vector<vector<vector<double>>> dp(N, vecotr<vector<double>> (N, vector<double>(K+1, 0)));
        vector<pair<int, int> > nextPos;
        for(int v = 1; v <=2; ++v) {
            for(int signx = -1; signx <= +1; signx+=2) {
                for (int signy = -1; signy <= +1; signy += 2) {
                    int x = signx*v;
                    int y = signy*(3-v);
                    nextPos.push_back({x, y});
                }
            }
        }
        vector<vector<double> > dp(N, vector<double>(N, 0));
        dp[r][c] = 1;
        for (int t = 1; t <= K; ++t) {
            vector<vector<double> > dp_next(N, vector<double>(N, 0));
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    if(dp[i][j] > 0) {
                        // split
                        for (size_t k = 0; k < nextPos.size(); ++k) {
                            int ii = i + nextPos[k].first;
                            int jj = j + nextPos[k].second;
                            if (ii >= 0 && ii < N && jj >=0 && jj <N) {
                                dp_next[ii][jj] += dp[i][j] / 8.0;
                            }
                        }
                    }
                }
            }
            dp.swap(dp_next);
        }
        double ans = 0;
        for (int i = 0; i < N; ++i) {
            vector<double>&v = dp[i];
            for(auto p:v){
                ans += p;
            }
        }
        return ans;
    }
};



int main() {

	Solution s;

	return 0;
}
