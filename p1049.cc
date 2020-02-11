#include "common.h"
class Solution {
public:
	//	01 backpack problem
	//	https://blog.csdn.net/u013445530/article/details/40210587
	//	there are N items (each of them volumn c[i] and value w[i]) and a pack with volumn V
	//  try to get the max value
	//  dp[i][v] means the max value we can get using first i items and a pack of valumn v
	//  dp[0][v] = 0, for v = 0, ... V
	//  transition:
	//  for item j, there are pick it or don't pick it
	//  1) if v-c[j] >= 0
	//		dp[i][v] = max(dp[i-1][v], dp[i-1][v-c[j]] + w[j]); 
	//  2) if v-c[j] < 0
	//		dp[i][v] = dp[i-1][v]; 
	//
	//	return dp[N][V]
    int lastStoneWeightII(vector<int>& stones) {
		//	https://www.acwing.com/solution/LeetCode/content/2139/
		// dp[i] means you can get a pile with sum = i, (that means another pile is total - i);
		// dp[0] = true
		// for stones[j], for sum = i, dp[i] = dp[i] || dp[i - stones[j]];
		// i >= stones[j]
		int total = accumulate(stones.begin(), stones.end(), 0);
		int half = total / 2;
		vector<bool> dp(half + 1, false);
		dp[0] = true;
		// order is important here
		for (size_t j = 0; j < stones.size(); ++j) { // left to right
			for (int i = half; i >= stones[j]; --i) { // right to left
				dp[i] = dp[i] || dp[i - stones[j]];
			}
		}
		for (int i = half; i >= 0; --i) {
			if (dp[i]) {
				return total - (i << 1);
			}
		}
		return total;	// dummy return value
	}

	
    int lastStoneWeightII_bad(vector<int>& stones) {
		// divide stones into two piles
		// if sum (p1) == sum(p2), then diff = 0, return 0
		// otherwise return the min(sum(p1) - sum(p2));
		// TLE
		sort(stones.begin(), stones.end());
		int total = accumulate(stones.begin(), stones.end(), 0);
		// backpack problem?
		int r = INT_MAX;
		dfs(stones, 0, 0, r, total);
		return r;
    }
private:
	void dfs(vector<int> stones, size_t start, int sum, int& r, int total) {
		if (start == stones.size()) {
			r = min(r, abs((sum << 1) - total));
			return;
		}
		int diff = ((sum + stones[start]) << 1) - total;
		if (diff >= r) {
			return;
		} else{
			sum += stones[start];
			r = min(r, abs(diff));
			if (!r) { return;}
			if (diff < r) {
				dfs(stones, start + 1, sum , r, total);
			}
			sum -= stones[start];	
		}
		if (!r) {
			return;
		}
		dfs(stones, start + 1, sum, r , total);
	}
};

int main() {

	vector<int> stones = {2,7,4,1,8,1};
	stones = {1,1,2,3,5,8,13,21,34,55,89,14,23,37,61,98};
	stones = {22,30,36,83,26,20,23,73,25,22,42,55,29,3,31,19,12,32,2,13,14,27,24,26};
	Solution s;
	cout << s.lastStoneWeightII(stones) << endl;


	return 0;
}
