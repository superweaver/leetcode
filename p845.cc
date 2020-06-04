#include "common.h"
// solution 2: use two vector to record the increasing length and decreasing length
class Solution {
public:
	int longestMountain(vector<int>& A) {
		int left = 0;
		int right = 0;
		int result = 0;
		A.push_back(INT_MAX);
		int n = A.size();
		for (int i = 1; i < n; ++i) {
			if (A[i] > A[i - 1]) {
				if (left > 0 && right > 0) {
					result = max(result, left + right + 1);
					left = right = 0;
				}
				left++;
			}
			else if (A[i] == A[i - 1]) {
				if (left > 0 && right > 0) {
					result = max(result, left + right + 1);
				}
				left = right = 0;
			}
			else {
				// A[i] < A[i-1]
				if (left > 0) {
					right++;
				}
			}
		}
		A.pop_back();
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
