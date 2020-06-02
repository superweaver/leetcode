#include "common.h"
class Solution {
  public:
    int numSubarrayBoundedMax(vector<int> &A, int L, int R) {
        size_t i = 0, j = 0, cnt = 0, delta = 0; // delta is the number of subarrays that will be
                                                 // added when this element got added
        // maintain an interval [i, j] so that A[i...j] satisfies
        // max of them is with [L, R]
        // if A[j] >= L && A[j] <= R
        // you can add it into previous interval, j++
        // and use A[j] as end of subarray, there will be new j-i+1 subarrays
        //
        //if A[j] > R
        //no such subarray ending at j can be added
        //so delta = 0, change i = j+1;
        //
        //if A[j] < L; :) interesting
        //you can add it to prevous interval
        // any subarray which is valid and ending at A[j-1]
        // can be appended with A[j], this is still a valid one
        // so delta is not changed;
        while (j < A.size()) {
            if (A[j] >= L && A[j] <= R)
                delta = j - i + 1; // this is the delta of cnt contributed by element j
            else if (A[j] > R) {
                delta = 0;
                i = j + 1;
            }// else { delta = delta;} // !!!
            cnt += delta;
            j++;
        }
        return cnt;
    }
};

int main() {

	Solution s;

	return 0;
}
