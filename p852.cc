#include "common.h"
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        // binary search
        int low = 0;
        int high = A.size() - 1;
        while(low  < high){
            int mid = low + (high - low) / 2;
            if(A[mid] < A[mid+1]){  // use mid + 1
                low = mid+1;
            }else{
                high = mid;
            }
        }
        return low;
    }
};

int main() {

	Solution s;

	return 0;
}
