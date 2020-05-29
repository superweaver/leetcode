#include "common.h"

class Solution {
public:
    // this is a more general solution
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int, int> count;
        for(auto n : nums){
            count[n]++;
        }
        vector<pair<int, int> > vnums;
        for(auto&p:count){
            vnums.push_back(p);
        }
        sort(vnums.begin(), vnums.end());
        int n = vnums.size();
        int r = 0;
        vector<int> dp(n, 0);  // using up to i nodes, the max earning you can get
        // if vnums[i].first != vnums[i-1].first +1
        // then dp[i] = dp[i-1] + vnums[i].first * vnums[i].second;
        // else 
        // case 1) don't use vnums[i].first, it is equivalent to dp[i-1]
        // case 2) use vnums[i], but because  vnums[i].first == vnums[i-1].first +1
        // vnums[i-1] can't be used
        // so dp[i] = max(dp[i-1], dp[i-2] + vnums[i].first * vnums[i].second);
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                dp[i] =  vnums[i].first * vnums[i].second;
            } else {
                if (vnums[i].first != vnums[i-1].first + 1) {
                    dp[i] = vnums[i].first * vnums[i].second + dp[i - 1];
                } else {
                    dp[i] =
                        max(dp[i - 1], vnums[i].first * vnums[i].second + ((i >= 2) ? dp[i - 2] : 0));
                }
            }
            r = max(r, dp[i]);
        }
        return r;
    }
};


int main() {

	Solution s;

	return 0;
}
