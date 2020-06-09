#include "common.h"
class Solution {
  public:
    vector<int> sortArrayByParityII(vector<int> &A) {
        int n = A.size();
        for (int i = 0, j = 1; i < n && j < n;) {
            while (i < n && (A[i] & 1) == (i & 1)) {
                i += 2;
            }
            while (j < n && (A[j] & 1) == (j & 1)) {
                j += 2;
            }
            if (i < n && j < n) {
                swap(A[i], A[j]);
                i += 2;
                j += 2;
            } else {
                break;
            }
        }
        return A;
    }
};

int main() {

	Solution s;

	return 0;
}
