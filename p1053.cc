#include "common.h"
class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& A) {
		// note: only one swap is allowed
		int n = A.size();
        int i = n - 1;
		// find first index i where A[i] > A[i+1]
        for (i = n - 2; i >= 0; --i) {
            if (A[i] > A[i + 1]) {
                break;
            }
        }
		if (i == -1) { // already the smallest permutation
			return A;
		}
		// from [i + 1 to n - 1] find the largest element < A[i]
		// for the same value, left one is used;
		int index = i + 1;
		for (int j = i + 1; j < n; ++j) {
			if (A[j] < A[i]) {
				if (A[j] > A[index]) {
					index = j;
				}
            } else {
				break;
            }
        }
		// swap A[index] A[i]
		swap(A[index], A[i]);
		return A;
    }
};

int main() {

	vector<int> A = {3, 2, 1};
	//A = {1, 1, 5}; // 1, 1, 5
	//A = {1, 9, 4, 6, 7}; // 1 7, 4, 6, 9
	//A = {3, 1, 1, 3}; // 1, 3, 1, 3
	Solution s;
	displayvector(s.prevPermOpt1(A));
	return 0;
}
