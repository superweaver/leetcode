#include "common.h"
//983. Minimum Cost For Tickets
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        // if there is an optimal solution
        // then first day is in single day pass or 7 days pass or monthly pass
        // pick the minimum
        vector<int> dp(n, INT_MAX);  // dp[i] is the mininum cost to cover subarray days[i..n-1]
        // dp[i] = one of bellow case 
        // 1) costs[0] + dp[i+1] , buy one day pass
        // 2) cost [1] + dp[k], k is the index >= i + 7
        // 3 cost [2] + dp[k], k is the first index >= 30;
        vector<int> cover = {1, 7, 30};
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < 3; ++j) {
                int right = 0;
                for (int k = i + 1; k < n; ++k) { // at most 30
                    if (days[k] - days[i] >= cover[j]){
                        right = dp[k];
                        break;
                    }
                }
                dp[i] = min(dp[i], costs[j] + right);
            }
        }
        return dp[0];
    }
};

int main() {
    vector<int> days = {1,4,6,7,8,20}, costs = {2,7,15};
	Solution s;
    cout << s.mincostTickets(days, costs) << endl;
	return 0;
}
