#include "common.h"
class Solution {
public:
    // need to do again :(
	// https://www.cnblogs.com/grandyang/p/6675879.html
	// https://blog.csdn.net/JackZhang_123/article/details/78807293
	// dp
    //
	// !!!
    // if there is path to generate the optimal solution, by inversing its steps.
    // there is a way to go back
    //
	// dp[i][j] means the min steps to get key[i...end] ready, 
    // and at begining its 12 position is pointing at index j of ring

	// note that right[i..end] has already in order
	// dp[i][j] = min(dp[i][j], dp[i+1][k] + step) , where ring[k] = key[i]
    //
	// step = min(abs(k-j), ring.size() - abs(k-j));
	int findRotateSteps(string ring, string key) {
		int n = ring.size();
		int m = key.size();
        vector<vector<int>> c2i(128);
        for (int i = 0; i < n; ++i) {
            c2i[ring[i]].push_back(i);
        }
		vector<vector<int> > dp(m + 1, vector<int>(n, INT_MAX));
		// note: dp[m][j] = 0 // already done
		dp[m] = vector<int>(n, 0);
        for (int i = m - 1; i >= 0; --i) { // key size
            for (int j = 0; j < n; ++j) { // ring size
                // this can be impoved
                /*
				for (int k = 0; k < n; ++k) { // last step, ring stops at key[k], which should be equal to key[i]
					if (key[i] == ring[k]) {	// dp[i][j] can be otained dp[i+1][k] and then key[i] = ring[k]
						int diff = abs(k - j);
						dp[i][j] = min(dp[i][j], dp[i + 1][k] + min(diff, n - diff));
					}
				}
                */
                const vector<int>& indices = c2i[key[i]];
                for (auto index : indices) {
                    int diff = abs(index - j);
                    dp[i][j] = min(dp[i][j], dp[i + 1][index] + min(diff, n - diff));
                }
			}
        }
        return dp[0][0] + m; // add m times spell
	}
};

int main() {

	Solution s;

	return 0;
}
