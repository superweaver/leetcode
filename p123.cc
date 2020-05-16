#include "common.h"
// 1) dp
//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/discuss/135704/Detail-explanation-of-DP-solution
// dp[k][i] is the max profit we can get from first i days' price by using k transactions
// dp[k][i] = max(dp[k][i-1], price[i-1] - price[j-1] + dp[k-1][j-1]), for j = 0, ... i - 1
//
class Solution{
  public:
    int maxProfit(vector<int>& prices) {
        // at most 2 times of transcation
       int n = prices.size(); 
       if (n == 0) {
           return 0;
       }
       const int K = 2;
       vector<vector<int>> dp(K + 1, vector<int>(n, 0));
       for (int k = 1; k <= K; ++k) {
           int spent = prices[0]; // spent is the min spent up on i-1
           for (int i = 1; i < n; ++i) {
               // 0, ... i - 2 was previously calculated
               spent = min(spent, prices[i - 1] - dp[k - 1][i - 1]);
               dp[k][i] = max(dp[k][i - 1], prices[i] - spent);
           }
       }
       // time O(Kn), space o(Kn)
       return dp[K][n - 1];
    }

    int maxProfit2(vector<int> &prices) {
        // at most 2 times of transcation
       int n = prices.size(); 
       if (n == 0) {
           return 0;
       }
       const int K = 2;
       vector<vector<int>> dp(K + 1, vector<int>(n, 0));
       //swap for loops
       vector<int> spent(K + 1, prices[0]);
       for (int i = 1; i < n; ++i) {
           for (int k = 1; k <= K; ++k) {
               spent[k] = min(spent[k], prices[i - 1] - dp[k - 1][i - 1]);
               dp[k][i] = max(dp[k][i - 1], prices[i] - spent[k]);
           }
       }
       return dp[K][n - 1];
    }
};



int main() {

    vector<int> prices = {3,3,5,0,0,3,1,4};
	Solution s;
    cout << s.maxProfit(prices) << endl;
    cout << s.maxProfit2(prices) << endl;

	return 0;
}
