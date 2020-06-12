#include "common.h"
class Solution {
public:
	int maxScoreSightseeingPair(vector<int>& A) {
		int n = A.size();
		int r = A[1] + A[0] + 0 - 1; // >= 1
        int pre_index = 0;           // previous index where A[pre_index] + pre_index is maximized
        if (A[0] + 0 < A[1] + 1) { 
			pre_index = 1;
		}
		for (int i = 2; i < n; ++i) {
			r = max(r, A[i] + A[pre_index] - i + pre_index);
            if (A[i] + i > A[pre_index] + pre_index) {
                pre_index = i;
            }
        }
		return r;
	}
};

int main() {

	Solution s;

	return 0;
}
