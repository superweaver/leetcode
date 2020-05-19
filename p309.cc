#include "common.h"

// method 1)
// buy[i] means upto day i, the max profit gained by a sequence ending with buy
// sell[i] means upto day i, the max profit gained by a sequence ending with sell
// rest[i] means upto day i, the max profit gained by a sequence ending with rest
// then we have
// buy[i] = max(buy[i-1] , rest[i-1] - price[i]);
// sell[i] = max(sell[i-1], buy[i-1] + price[i]);
// rest[i] = max(buy[i-1], rest[i-1], sell[i-1]);
// simplify:
// at any day i; buy[i] <= rest[i] <= sell[i]
// so we have rest[i] = sell[i-1];
// buy[i] = max(buy[i-1], sell[i-2] - price[i]);
// sell[i] = max(buy[i-1] + price[i], sell[i-1]);

// method 2
// p_t0 upto day t, the max profit when hold 0 share
// p_t1 upto day t, the max profit when hold 1 share
// if we have no cooldown
// p[t][0] = max(p[t-1][1] + price[t], p[t-1][0]);
// p[t][1] = max(p[t-1][0] - price[t], p[t-1][1]);
// if we have one day cooldown
//  p[t][0] = max(p[t-1][1] + price[t], p[t-1][0]);
//  p[t][1] = max(p[t-2][0] - price[t], p[t-1][1]);// !!!!

class Solution {
  public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        int p_t0 = 0;
        int p_t1 = INT_MIN;
        int p_t0_pre = 0;
        for (int i = 0; i < n; ++i) {
            int p_t0_old = p_t0; // cache it
            // int p_t0_new = max(p_t1 + prices[i], p_t0);
            // int p_t1_new = max(p_t0_pre - prices[i], p_t1);
            // p_t0 = p_t0_new;
            // p_t1 = p_t1_new;
            p_t0 = max(p_t1 + prices[i], p_t0);
            p_t1 = max(p_t0_pre - prices[i], p_t1);
            p_t0_pre = p_t0_old;
        }
        return p_t0;
    }
};

int main() {

	Solution s;

	return 0;
}
