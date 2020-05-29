#include "common.h"

class Solution {
public:    
	int minStickers(vector<string>& stickers, string target) {
		// dp
		// n = target.size();
		// then there are 2^n subsets of target
		// dp[i] is the minimum stickers to form ith subset
		// i = (xx0llxxx) in binary form
		// its corresonding subset is to take character where bit == 1
		// base case is dp[0] = 0;
		int n = target.size();
		int m = (1 << n);
		vector<int> dp(m, INT_MAX);
		dp[0] = 0;
		for (int i = 0; i < m; ++i) {
            // i is current state
            if (dp[i] == INT_MAX) {
                // there is no way to get state i
                continue;
            }

            // by adding some characters to current state
			// we can update the min stickers for next state;
			// similar to coin change question
           
			for (auto& s : stickers) {
				int next = i;
				for (auto c : s) {
					for (int k = 0; k < n; ++k) {
                        if (target[k] == c) { // left most char is target [0]
                            if (((next>> k) & 1) == 0) {
								// change to next state	
								next |= (1 << k);
								break;
							}
							else {
								// it is possible that current state has already contains this character at target k
								continue;
							}
                        }
                    }
				}
				// next state can be obtained by sticker s
				dp[next] = min(dp[next], dp[i] + 1);
			}
		}
		return dp[m - 1] == INT_MAX ? -1 : dp[m - 1];
	}
};
class Solution_my {
public:
	int minStickers(vector<string>& stickers, string target) {
		if (target.empty()) return 0;
		unordered_map<char, int> t;
		for (auto c : target) {
			t[c]++;
		}
		int len = t.size();
		int n = stickers.size();
		vector<vector<int>> charSources(n, vector<int>(26, 0));
		for (int i = 0; i < n; ++i) {
			string& s = stickers[i];
			vector<int>& count = charSources[i];
			for (auto c : s) {
				count[c - 'a']++;
			}
		}
		//check if it is impossible
		for (auto&p : t) {
			char c = p.first;
			// check if c exists in some words
			bool noexist = true;
			for (auto&count : charSources) {
				if (count[c - 'a']) {
					noexist = false;
					break;
				}
			}
			if (noexist) {
				return -1;
			}
		}
		// how to solve it ?
		// convex optimization

		// dp
		// with memo // a kind of brute froce
		//	https://www.cnblogs.com/grandyang/p/8468045.html
		unordered_map<string, int> memo;
		// base case
		memo[""] = 0;
		return helper(charSources, target, memo);
	}
	int helper(const vector<vector<int> >& freq, string target, unordered_map<string, int>& memo) {
		if (memo.count(target)) return memo.at(target);
		int result = INT_MAX;
		int n = freq.size();
		// target may not be the original target
		vector<int> freq_t(26, 0);
		for (auto c : target) {
			freq_t[c - 'a']++;
		}
		for (int i = 0; i < n; ++i) {
			if (freq[i][target[0] - 'a'] == 0) continue; // at least have first letter in target
			string t = "";
			// form new target
			for (int j = 0; j < 26; ++j) {
				if (freq_t[j] > freq[i][j]) { // need more freq_t[j]
					t += string(freq_t[j] - freq[i][j], 'a' + j);
				}
			}
			// try to find the min for new target
			int r = helper(freq, t, memo);
			if (r != -1) {
				result = min(result, r + 1);
			}
		}
		memo[target] = (result == INT_MAX) ? -1 : result;
		return memo[target];
	}
};

int main() {

	Solution s;

	return 0;
}
