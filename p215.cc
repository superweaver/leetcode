#include "common.h"

class Solution {
  public:
    // there is nth_element after c++17
    int findKthLargest(vector<int> &nums, int k) {
        // fast selection
        int n = nums.size();
        if (n == 0) {
            return INT_MIN;
        }
        // note : kth largest element 
        // instead of kth elment in ascending order
        return quickSelect(nums, 0, n - 1, n - k + 1);
    }
    int quickSelect(vector<int> &nums, int start, int end, int k) {
        // pick nums[start] as pivot
        int pivot = nums[start];
        // put it to the end
        swap(nums[start], nums[end]);
        // PivotIndex is next place where to put element < than pivot
        int PivotIndex = start;
        // end has been used
        // i >= PivotIndex
        for (int i = start; i < end; i++) {
            if (nums[i] < pivot) {
                swap(nums[i], nums[PivotIndex]);
                PivotIndex++;
            }
        }
        swap(nums[PivotIndex], nums[end]);
        int len = (PivotIndex - start + 1); // 1 +  how many element tha tis less than pivot
        if (k == len)
            return nums[PivotIndex];
        if (k < len) {
            quickSelect(nums, start, PivotIndex - 1, k);
        } else {
            quickSelect(nums, PivotIndex + 1, end, k - len);
        }
    }
};

int main() {

	Solution s;

	return 0;
}
