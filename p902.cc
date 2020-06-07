#include "common.h"
class Solution {
  public:
    int atMostNGivenDigitSet(vector<string> &D, int N) {
        // D is increasing 
        int Np = N;
        int n = 0;
        vector<int> vN;
        while (Np) {
            vN.push_back(Np % 10);
            n++;
            Np /= 10;
        }
        // put MSB ahead 
        reverse(vN.begin(), vN.end());

        int result = 0;
        int size_D = D.size();
        // dp[i] is how many different ways we can get from string of length i
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        // len < n;
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1] * size_D;
        }
        // check len == n
        helper(dp, vN, D, 0);

        for (auto i : dp) {
            result += i;
        }
        result -= 1; // !!!remove empty
        return result;
    }

  private:
    void helper(vector<int> &dp, vector<int> &vN, vector<string> &D, int index) {
        if (index == (int)vN.size()) {
            // one way, equal
            dp.back() += 1;
            return;
        }
        int v = vN[index];
        char cv = v + '0';
        for (size_t i = 0; i < D.size(); ++i) {
            if (D[i][0] < cv) {
                // dp.size() - (index + 2) is length of right side
                dp.back() += dp[dp.size() - (index + 2)];
            } else if (D[i][0] == cv) {
                helper(dp, vN, D, index + 1);
                break;
            } else {
                // > cv, can't use it
                break;
            }
        }
    }
};

int main() {

	Solution s;

	return 0;
}
