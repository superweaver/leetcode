#include "common.h"
class Solution {
public:
	// solved by myself, not optimal but brute force
    int tallestBillboard_bf(vector<int>& rods) {
		int upper = accumulate(rods.begin(), rods.end(), 0);
		upper /= 2;
		vector<vector<int>> sum2index(upper + 1);
		sort(rods.begin(), rods.end()); 
		int key = 0;	
		helper(rods, upper, 0, 0, key, sum2index);
		for (int i = upper; i >= 0; --i) {
			if (sum2index.size() >= 2) {
				vector<int> & v = sum2index[i];
				for (size_t j = 0; j < v.size(); ++j) {
					for (size_t k = j + 1; k < v.size(); ++k) {
						if (!(v[j] & v[k])) {
							return i;
						}
					}
				}
			}
		}
		return 0;
    }
	// https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-956-tallest-billboard/
	// dp
    int tallestBillboard(vector<int>& rods) {
		int upper = accumulate(rods.begin(), rods.end(), 0);
		// dp[n][i] is the max of common length of left piles and right piles by using first n rods, resulting a difference of height of i
		// dp[0][0] = 0;
		// for any incoming height h
		// there are sevral choices to put h 
		// 1) don't use h, then dp[n][i] = dp[n-1][i] // no point for solution
		// 2) put h to higher pile, then dp[n][i+h] = dp[n-1][i];
		// 3) put h to lower piles, then there are two cases
		//		a) h <= i, then dp[n][i-h] = dp[n-1][i] + h;
		//		b) h > i, then dp[n][h - i] = dp[n-1][i] + i;
		//	for both cases, dp[n][|i-h]] = dp[n-1][i] + min(h, i);
		// the max difference will be upper - 0 = upper;
		//
		// return dp[n][0];
		vector<int> dp(upper+1, -1);
		dp[0] = 0;
		for (auto h : rods) {
			vector<int> current(dp);
			for (int i = 0; i <= upper - h; ++i) {
				if (current[i] < 0) {
					continue;
				}
				dp[i+h] = max(current[i+h], current[i]);
				int& v = dp[abs(i-h)];
				v = max(v, current[i] + min(h,i));
			}
		}
		return dp[0];
	}
private:
	void helper(vector<int>& rods, int upper, int sum,  size_t start, int key, vector<vector<int>>& sum2index) {
		if (start >= rods.size()) {
			return ;
		}
		if (sum + rods[start] <= upper) {
			// no pick
			helper(rods, upper, sum, start+1, key << 1, sum2index);
			// pick
			sum += rods[start];
			key = ((key) << 1) + 1;
			sum2index[sum].push_back(key << (rods.size() - start - 1));
			helper(rods, upper, sum, start+1, key, sum2index);
		} else {
			return ;
		}
	}
};
int main() {

	vector<int> A = {1, 2, 3, 6};
	Solution s;
	cout << s.tallestBillboard(A) << endl;
	return 0;
}
