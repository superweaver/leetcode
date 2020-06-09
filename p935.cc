#include "common.h"
class Solution {
  public:
    int knightDialer(int N) {
        const int D = 10;
        const int Mod = (int)1e9 + 7;
        vector<long long> current(D, 1);
        vector<vector<int>> jump(D);
        jump[0] = {4, 6};
        jump[1] = {8, 6};
        jump[2] = {7, 9};
        jump[3] = {4, 8};
        jump[4] = {3, 9, 0}; // fuck it
        jump[5] = {};
        jump[6] = {1, 7, 0}; // fuck it
        jump[7] = {2, 6};
        jump[8] = {1, 3};
        jump[9] = {4, 2};

        for (int i = 1; i < N; ++i) {
            vector<long long> next(D, 0);
            for (int j = 0; j < D; ++j) {
                for (auto k : jump[j]) {
                    next[k] += current[j];
                    next[k] %= Mod;
                }
            }
            current.swap(next);
        }
        long long r = 0;
        for (auto i : current) {
            r = (r + i) % Mod;
        }
        return (int)r;
    }
};

int main() {

	Solution s;

	return 0;
}
