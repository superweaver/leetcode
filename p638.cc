#include "common.h"
//https://www.cnblogs.com/grandyang/p/7261663.html
//https://github.com/YaokaiYang-assaultmaster/LeetCode/blob/master/LeetcodeAlgorithmQuestions/638.%20Shopping%20Offers.md
// DFS or DP
class Solution {
public:
	int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
		// assume special offer is cheaper
		// assume price is not empty
		if (needs.empty()) {
			return 0;
		}
		return helper(price, special, needs);
	}
private:
	//unordered_map<vector<int>, int> cache;
	int helper(vector<int>& price, vector<vector<int> > & special, vector<int>& needs) {
		// can add memorization for needs,
		// need to convert needs to string for hash
		//	if (cache.count(needs)) {
		//		return cache[needs];
		//	}
		int n = price.size();
		int total = 0;
		// no special offer
		for (int i = 0; i < n; ++i) {
			total += price[i] * needs[i];
		}
		// try special offer
		for (auto offer : special) {
			// check if we can use this offer
			bool isValid = true;
			for (int i = 0; i < n; ++i) {
				needs[i] -= offer[i];
				if (needs[i] < 0) {
					isValid = false;
					// don't break here
				}
			}
			if (isValid) {
				total = min(total, helper(price, special, needs) + offer.back());
			}
			// trace back
			for (int i = 0; i < n; ++i) {
				needs[i] += offer[i];
			}
		}
		//cache[needs] = total;
		return total;
	}
};

int main() {

	Solution s;

	return 0;
}
