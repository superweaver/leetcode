#include "common.h"
// http://www.cnblogs.com/grandyang/p/5727892.html
class Solution {
  public:
    int kthSmallest(vector<vector<int>> &nums, int k) {
        int n = nums.size();
        int low = nums[0][0];
        int high = nums[n - 1][n - 1]; 
        while (low < high) {
            int mid = low + (high - low) / 2;
            int count = search_less_equal(nums, mid);
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid; // this is the key
            }
        }
        // low = high !!
        return low;
    }

    int kthSmallest2(vector<vector<int>> &nums, int k) {
        // find the least element x so that the number of element in matrix <= x is >= k
        int n = nums.size();
        int low = nums[0][0];
        int high = nums[n - 1][n - 1] + 1; // high is excluded
        while (low < high) {
            int mid = low + (high - low) / 2;
            int count = search_less_equal(nums, mid);
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid; // this is the key
            }
        }
        return low;
    }

  private:
    int search_less_equal(vector<vector<int>> &nums, int x) {
        // start from left bottom
        int n = nums.size();
        int i = n - 1;
        int j = 0;
        int count = 0;
        while (i >= 0 && j < n) {
            if (nums[i][j] <= x) {
                count += i + 1;
                ++j;
            } else {
                --i;
            }
        }
        return count;
    }
};

int main() {
    vector<vector<int>> matrix = { { 1, 5, 9}, {10, 11, 13}, {12, 13, 15} };
    int k = 8;
	Solution s;
    cout << s.kthSmallest(matrix, k) << endl;
    cout << s.kthSmallest2(matrix, 9) << endl;

	return 0;
}
