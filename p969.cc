#include "common.h"
class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
		// greedy
		int n = A.size(); 
		vector<int> result;
		for (int i = n - 1; i >= 0; i--) {
			if (A[i] == i + 1) continue;
			// try to find it before i
			for (int j = 0; j < i ; ++j) {
				if (A[j] == i + 1) {
					if (j > 0) {
						result.push_back(j + 1);	
					}
					for (int k = 0; k < j;) {
						swap(A[k++], A[j--]);
					}
					break;
				}
			}
			result.push_back(i + 1);
			for (int j = i, k = 0; k < j; ){
				swap(A[k++], A[j--]);
			}
		}
		return result;
    }
};
int main() {
	vector<int> A = {3,2,4,1};
	Solution s;
	displayvector(s.pancakeSort(A));
	return 0;
}
