#include "common.h"
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
       sort(A.begin(), A.end());
       int expect = INT_MIN;
       int result = 0;
       for (size_t i = 0; i < A.size(); ++i) {
           if(A[i] > expect) {
               expect = A[i] + 1;
           } else {  // <=
               result += (expect++ - A[i]);
           }
       }
       return result;
    }
};



int main() {

	Solution s;

	return 0;
}
