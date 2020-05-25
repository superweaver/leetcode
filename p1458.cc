#include "common.h"
class Solution {
  public:
    int maxDotProduct(vector<int> &nums1, vector<int> &nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, INT_MIN));
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                // dp[i+1][j+1] = max(dp[i][j], dp[i+1][j], dp[i][j+1], (dp[i][j]>0) ? dp[i][j] : 0
                // + nums1[i]*nums2[j]);
                // this always holds dp[i+1][j] >= dp[i][j]
                //
                dp[i + 1][j + 1] =
                    max(max(dp[i][j + 1], dp[i + 1][j]), max(dp[i][j], 0) + nums1[i] * nums2[j]);
            }
        }
        return dp[n1][n2];
    }
};

int main() {

    vector<int> nums1 = {2,1,-2,5}, nums2 = {3,0,-6}; // 18
    //nums1 = {3,-2}, nums2 = {2,-6,7}; // 21
    nums1 = {-5, 3, -5, -3, 1};
    nums2 = {-2, 4, 2, 5, -5}; // 50
    nums1 = {-5, -1, -2};
    nums2 = {3, 3, 5, 5}; // -3

    nums1 = {-1,-1}, nums2 = {1,1};// -1 

    nums1 = {-3,-8,3,-10,1,3,9};
    nums2 = {9,2,3,7,-9,1,-8,5,-1,-1}; // 200



    Solution s;
    cout << s.maxDotProduct(nums1, nums2) << endl;

	return 0;
}
