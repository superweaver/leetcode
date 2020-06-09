#include "common.h"
class Solution {
public:
	int minDeletionSize(vector<string>& A) {
		if (A.empty() || A[0].empty()) return 0;
		int m = A.size();
		int n = A[0].size();
		int result = 0;
        // !!! each remaining column in A is in non-decreasing sorted order.
        // not remaining string
		for (int j = 0; j < n; ++j) { // column
			char pre = 'a' - 1;
			bool isValid = true;
			for (int i = 0; i < m; ++i) {
                char c = A[i][j];
				if (c < pre) {
					isValid = false;
					break;
				}
                pre = c;
			}
			if (!isValid) {
				result++;
			}
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
