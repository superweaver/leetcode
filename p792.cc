#include "common.h"

class Solution {
public:
	int numMatchingSubseq(string S, vector<string>& words) {
		vector<vector<int>> index(128);
		int n = S.size();
		for (int i = 0; i < n; ++i) {
			index[S[i]].push_back(i);
		}
		int count = 0;
		for (auto&s : words) {
			count += isSubseq(index, s, n);
		}
		return count;
	}
private:
	bool isSubseq(vector<vector<int>> &index, const string&s, int n) {
		int m = s.size();
		if (m > n) {
			return false;
		}
		int upbound = n;
		for (int j = m - 1; j >= 0; --j) {
			vector<int>& v = index[s[j]];
            // good to use this
			auto it = upper_bound(v.rbegin(), v.rend(), upbound, greater<int>());
			if (it == v.rend()) {
				return false;
			}
			else {
				upbound = *it;
			}
		}
		return true;
	}
};

int main() {

	Solution s;

	return 0;
}
