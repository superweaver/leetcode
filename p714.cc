#include "common.h"

class Solution_1 {
public:
	int maxProfit(vector<int>& prices, int fee) {
		int n = prices.size();
		if (n < 2) return 0;
		int r = 0;
		int leftmin = prices[0];
		int prevSellout = INT_MAX;
		int prevProfit = 0;
		for (int i = 1; i < n; ++i) {
			int deltaP1 = prices[i] - prevSellout;
			int deltaP2 = prices[i] - leftmin - fee;
			if (deltaP1 > deltaP2 && deltaP1 > 0) {
				prevSellout = prices[i];
				leftmin = prices[i];
				r += deltaP1;
			}
			else if (deltaP2 > deltaP1 && deltaP2 > 0) {
				prevSellout = prices[i];
				leftmin = prices[i];
				r += deltaP2;
			}
			else if (deltaP1 == deltaP2 && deltaP1 > 0) {
				// no update
				prevSellout = prices[i];
				leftmin = prices[i];
				r += deltaP1;
			}
			else {
				leftmin = min(leftmin, prices[i]);
			}
		}
		return r;
	}
};

// https://www.hrwhisper.me/leetcode-best-time-to-buy-and-sell-stock-i-ii-iii-iv/
/*
双状态DP，类似于Best Time to Buy and Sell Stock with Cooldown

sell 考虑第i天是否卖出，buy考虑第i天是否买入

则有：
sell[i] = max(sell[i-1], buy[i-1] + price[i] - fee)
buy[i] = max(buy[i-1], sell[i-1] - price[i])
sell[0] = 0;
buy[0] = -price[0];
*/


class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if(prices.size() < 2) return 0;
        int sell = 0, buy = -prices[0];
        for(size_t i = 1; i < prices.size(); i++){
            sell = max(sell, buy + prices[i] - fee);
            buy = max(buy, sell - prices[i]);
        }
        return sell;
    }
};

int main() {

	Solution s;

	return 0;
}
