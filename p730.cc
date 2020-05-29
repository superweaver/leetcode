#include "common.h"

class Solution {
	// http://zxi.mytechroad.com/blog/dynamic-programming/leetcode-730-count-different-palindromic-subsequences/
	// not solved :(
public:
	int countPalindromicSubsequences(string S) {
		int n = S.size();
		cache = vector<int>((n+1)*n, 0); // key = n * i + j;
		vector<vector<int>> occurance(4); // record the index of each char, only has a, b, c, d
		for (int i = 0; i < n; ++i) {
			occurance[S[i] - 'a'].push_back(i);
		}
		vector<int> prevOccurance(n, -1);
		vector<int> nextOccurance(n, n);
		for (auto&v : occurance) {
			int pre = -1;
			for (size_t i = 0; i < v.size(); ++i) {
				prevOccurance[v[i]] = pre;
				if (pre >= 0) {
					nextOccurance[pre] = v[i];
				}
				pre = v[i];
			}
		}
		return helper(S, 0, n - 1, n, prevOccurance, nextOccurance);
	}
private:
	const int Mode = 1000000007;
	vector<int> cache;
	int helper(const string& s, int start, int end, int n, const vector<int>& prev, const vector<int>& next) {
		// dp[i][j]
		// if s[i] != s[j];
		// dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]
		// if s[i] == s[j]
		// if there is no s[i] in [i+1...j-1], dp[i][j] = 2*dp[i+1][j-1] + 2; // a and aa
		// if there is one s[i] in [i+1...j-1], dp[i][j] = 2*dp[i+1][j-1] + 1; // only aa, since a has been calculated before
		// if there are more than two s[i] in [i+1...j-1], dp[i][j] = 2*dp[i+1][j-1] -dp[l+1][r-1]
		if (start > end) return 0;
		if (start == end) return 1;// no need to put it cache;
		int key = n * start + end;
		if (cache[key] > 0) return cache[key];
		// calculate
		long long result = 0;  // long is not enough :(
		if (s[start] != s[end]) {
			result = helper(s, start + 1, end, n, prev, next);
			result += helper(s, start, end-1, n, prev, next);
			result -=  helper(s, start+1, end-1, n, prev, next);
		} else {
			int l = next[start];
			int r = prev[end];
			result = 2 *  helper(s, start + 1, end - 1, n, prev, next);
			if (r < l) {
				result += 2;
			}
			else if (l == r) {
				result += 1;
			} else {
				result -= helper(s, l + 1, r - 1, n, prev, next);
			}
		}
		result = (result + Mode) % Mode;
		cache[key] = (int)result;
		return cache[key];
	}
};

int main() {

	Solution s;

	return 0;
}
