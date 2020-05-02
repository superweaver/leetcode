#include "common.h"

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int n = candies.size();
        vector<bool> result(n, true);
        int m = candies[0];
        // left to right
        for (int i = 1; i < n; ++i) {
            // comparing candies[i] + extraCandies with max of left
             result[i] = (candies[i] + extraCandies) >= m;
            // update m
            m = max(m, candies[i]);
        }
        // right to left
        m = candies[n-1];
		for(int i = n - 2; i >= 0; --i)
		{
			if (result[i]) { // skip it if result[i] is false
				// comparing candies[i] + extraCandies with max of left
				result[i] = (candies[i] + extraCandies) >= m;
			}
			// update m
			m = max(m, candies[i]);
		}
        return result;
	}

    vector<bool> kidsWithCandies2(vector<int>& candies, int extraCandies) {
        int n = candies.size();
        vector<int>  left_max(n + 1, INT_MIN); // the max value of firt i element in candies from left to right
        for (int i = 1; i <= n; ++i) {
			left_max[i] = max(left_max[i - 1], candies[i - 1]);
		}
        vector<int> right_max(n + 1, INT_MIN);
		for(int i = 1; i <= n; ++i)
		{
			right_max[i] = max(right_max[i - 1], candies[n - i]);
		}
        vector<bool> result(n, true);
        for (int i = 0; i < n; ++i) {
			result[i] = (extraCandies + candies[i]) >= max(left_max[i], right_max[n - i - 1]);
		}
        return result;
	}
};

int main() {
    vector<int> candies = {2,3,5,1,3};
    int extraCandies = 3;
//candies = {4,2,1,1,2}, extraCandies = 1;
//candies = {12,1,12}, extraCandies = 10;


	Solution s;
    displayvector(s.kidsWithCandies(candies, extraCandies));

	return 0;
}
