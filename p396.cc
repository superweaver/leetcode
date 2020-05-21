#include "common.h"
class Solution {
public:
	int maxRotateFunction(vector<int>& A) {
		int n = A.size();
		long totalSum = 0;
		for (int i = 0; i < n; ++i) {
			totalSum += A[i];
		}
		long maxV = INT_MIN;
		int k = 0;
		long Fk = 0;
		for (int i = 0; i < n; ++i) {
			Fk += i * A[i];
		}
		maxV = max(maxV, Fk);
		// delta = (A[0]+...+A[n-k-1]) - (n-1)A[n-k] + (A[n-k+1]+...+ A[n-1]) = Fk[k]-Fk[k-1]
		// delta = (A[0] + ... A[n-1]) - n*A[n-k];
		for (k = 1; k < n; ++k) {
			Fk += totalSum - n * A[n - k];
			maxV = max(maxV, Fk);
		}
		return (int)maxV;
	}
};

int main() {

	Solution s;

	return 0;
}
