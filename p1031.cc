#include "common.h"
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& A, int L, int M) {
		// assume there is a separating index k	
		// 1) find the largest sum of subarry of length L up to index k (exclusive) ([0, k)) from left to right
		// 2) find the larget sum of subarry of  length M in range [k, A.size()) from right to left
		// then we can get max Sum of two NoOverlap subarry for differnt separating index k
		//
		// swap L and M, do it again
		// return max of these two
		int r1 = helper(A, L, M);
		int r2 = (L == M) ? r1 : helper(A, M, L);
		return max(r1, r2);
    }
private:
	int helper(vector<int>&A, int L, int M) {
		int n = A.size();
		vector<int> l2r(n + 1, 0);
		int sum = 0;
		for (int i = 0; i < L; ++i) {
			sum += A[i];	
		}
		for (int i = L; i <= n; ++i) {
			l2r[i] = max(l2r[i-1] , sum);
			if (i == n) {
				break;
			}
			sum += A[i];
			sum -= A[i-L];
		}
		vector<int> r2l(n + 1, 0);
		sum = 0;
		for (int j = n - M; j < n; ++j) {
			sum += A[j];
		}
		for (int j = n - M ; j >= 0; --j) {
			r2l[j] = max(r2l[j + 1], sum);
			if (j == 0){
				break;	
			}
			sum += A[j - 1];
			sum -= A[j - 1 + M];
		}
		int r = 0;
		for (int k = L; k + M <= n; ++k) {
			r = max(r, l2r[k] + r2l[k]);
		}
		return r;
	}
};

int main() {
	vector<int> A = {0,6,5,2,2,5,1,9,4};
	int L = 1, M = 2; // 20
	A = {3,8,1,3,2,1,8,9,0}, L = 3, M = 2; // 29
	A = {2,1,5,6,0,9,5,0,3,8}, L = 4, M = 3; // 31
	A = {1, 0, 3}, L = 1, M = 2;
	Solution s;
	cout << s.maxSumTwoNoOverlap(A, L, M) << endl;
	return 0;
}
