#include "common.h"
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        // it is equivalent to the find kth smallest element in the sorted matrix
        // here it is just half of the matrix;
        // (view it as square, it is a sorted matrix;)
        //
        // A[i][j] with size n by n
        // A[i][j] = nums[i] - num[n-1-j] , i > n-1-j
        // first row has nothing
        // A[1][n-1] = nums[1] - nums[0] has one element
        // A[i][n-1] = nums[i] - nums[0] it is sorted in that column
        // for last row;
        // A[n-1][j] = nums[n-1] - nums[n-1-j]  it is also sorted
        int low = INT_MAX;
        for (int i = 1; i < n; ++i) {
            low = min(low, nums[i] - nums[i-1]);
        }
        int high = nums[n-1] - nums[0];
        while(low < high) {
            int mid = low + (high - low) / 2;
            int count = count_less_equal(nums, mid, n);
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid; // good !
            }
        }
        return high;
    }
private:
    inline int getValue(vector<int>& nums, int i, int j, int n)
    {
        return nums[i] - nums[n - 1 - j];
    }
    int count_less_equal(vector<int>&nums, int v, int n) {
        int count = 0;
        int i = 1;
        int j = n - 1;
        // top right
        // row by row
        //while (i <= n && j >= 1 && i + j > n - 1) {
        while (i < n && j >= 1) {
            if (getValue(nums, i, j, n) <= v) {
                count += (i + j) - (n - 1);
                ++i;
            } else {
                --j;
            }
        }
        return count;
    }
};


int main() {

	Solution s;

	return 0;
}
