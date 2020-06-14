#include "common.h"
class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        vector<int> result(prices);
        int n = prices.size();
        stack<int> s;
        s.push(n-1);
        for (int i = n - 2; i >= 0; --i) {
            while(!s.empty() && prices[s.top()] > prices[i]) {
                s.pop();
            }
            result[i] -= s.empty() ? 0 : prices[s.top()];
            s.push(i);
        }
        return result;
    }
};

int main() {
    vector<int> prices = {8, 4, 6, 2, 3};
    Solution s;
    displayvector(s.finalPrices(prices));
	return 0;
}
