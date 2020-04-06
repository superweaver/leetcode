#include "common.h"
class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
		int n = stoneValue.size();
        vector<int> suffix_sum(n + 1, 0);
		// 1 <= values.length <= 50000
		// -1000 <= values[i] <= 1000
		for (int i = n -1 ; i>= 0; --i) {
			suffix_sum[i] = suffix_sum[i+1] + stoneValue[i];
		}
        vector<int> cache(n, INT_MIN);  // cache[i] is the max value,  current player  can get, starting from index i
		// base
		// base is not correct
		/*
        for (int k = 1; k <= 3; ++k) {
            if (n - k < 0) {
                break;
			}
			int sum = 0;
            for (int i = n - k; i < n; ++i) {
				sum += stoneValue[i];
                cache[n - k] = max(cache[n - k], sum);
            }
        }
		*/
        cache[n - 1] = stoneValue[n - 1];
        suffix_sum.push_back(0);  // i == n + 1
        stoneValue.push_back(0);  // i == n
		cache.push_back(0); // i == n
		cache.push_back(0); // i == n + 1

        for (int i = n - 2; i >= 0; --i) {
            int sum = 0;
            for (int k = 0; k < 3; ++k) {  // n - 2 + 2 = n
                // if (i + k >= n) { break; }
                sum += stoneValue[i + k];
				assert(i + k < (int)stoneValue.size());
                //cache[i] = max(cache[i], sum + ((i + k + 1 < n) ? (suffix_sum[i + k + 1] - cache[i + k + 1]) : 0));
                cache[i] = max(cache[i], sum + (suffix_sum[i + k + 1] - cache[i + k + 1]));
            }
        }
        int alice = cache[0];
		int bob = suffix_sum[0] - cache[0];
		if (alice == bob) {
			return "Tie";
		} else if (alice > bob) {
			return "Alice";
		} else {
			return "Bob";
		}
    }
};

int main() {
    vector<int> stoneValue{ 1, 2, 3, -1, -2, -3, 7 }; // alice
	//stoneValue = {-1, -2, -3}; // Tie
//	stoneValue = {1, 2, 3, 6}; // Tie
//	stoneValue = {1, 2, 3, -9}; // alice
	stoneValue = {1, 2, 3, 7}; // Bob


    Solution s;
	cout << s.stoneGameIII(stoneValue) << endl;

	return 0;
}
