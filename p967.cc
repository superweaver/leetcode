#include "common.h"
class Solution {
public:
	vector<int> numsSameConsecDiff(int N, int K) {
        vector<int> result;
        if(N == 1) { // tricky and stupid
            for(int i = 0; i < 10; ++i){
                result.push_back(i);
            }
            return result;
        }
		vector<vector<int>> candidate(10);
		for (int i = 0; i < 10; ++i) {
			if (i - K >= 0) {
				candidate[i].push_back(i - K);
			}
			if (i + K < 10) {
				candidate[i].push_back(i + K);
			}
			if (K == 0) {
				candidate[i].pop_back();
			}
		}
		int bound = (int)pow(10, N - 1) - 1;
		for (int i = 1; i < 10; ++i) {
			// i is the leading digit
			if (!candidate[i].empty()) {
				helper(i, 1, result, N, candidate);
			}
		}
		return result;
	}
private:
	void helper(int pre, int len, vector<int>&result, int N, const vector<vector<int>>& candidate) {
		if (len == N) {
			result.push_back(pre);
			return;
		}
		int lastdigit = pre % 10;
		pre *= 10;
		const auto& c = candidate[lastdigit];
		for (auto i : c) {
			helper(pre + i, len + 1, result, N, candidate);
		}
	}
};

int main() {

	Solution s;

	return 0;
}
