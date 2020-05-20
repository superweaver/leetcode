#include "common.h"
class Solution {
  public:
      // https://leetcode.com/problems/create-maximum-number/discuss/77287/C%2B%2B-16ms-FASTEST-beats-97.
    vector<int> maxNumber(vector<int> &nums1, vector<int> &nums2, int k) {
        vector<int> result(k);
        vector<int> tmp_result(k);
        vector<vector<int>> max_num1(k + 1);
        vector<vector<int>> max_num2(k + 1);
        // dp is good
        genDP(nums1, max_num1, k);
        genDP(nums2, max_num2, k);

        for (int i = 0; i <= k; i++) {
            if (max_num1[i].size() + max_num2[k - i].size() < k) {
                continue;
            }
            merge(tmp_result, max_num1, max_num2, i, k);
            if (result.empty() || smaller(result, tmp_result)) {
                result = tmp_result;
            }
        }
        return result;
    }

  private:
    void genDP(vector<int> &nums, vector<vector<int>> &max_num, int k) {
        int i, start;
        for (start = 0; nums.size() > 0; start = (i == 0 ? 0 : i - 1)) {
            if (nums.size() <= k) {
                // nums.size() is changing
                max_num[nums.size()] = nums;
            }
            // find i where nums[i] < nums[i+1]
            // then nums[i] should be erased
            for (i = start; i + 1 < nums.size() && nums[i] >= nums[i + 1]; i++)
                ;
            nums.erase(nums.begin() + i);
        }
    }

    void merge(vector<int> &tmp_result, const vector<vector<int>> &max_num1,
               const vector<vector<int>> &max_num2, int n, int k) {
        int i, j;
        const vector<int>& v1 = max_num1[n];
        const vector<int>& v2 = max_num2[k-n];
        int n1 = v1.size();
        int n2 = v2.size();
        for (i = j = 0; i < n1 && j < n2;) {
            int ii, jj;
            for (ii = i, jj = j; ii < n1 && jj < n2; ii++, jj++) {
                if (v1[ii] != v2[jj]) {
                    break;
                }
            }
            if (jj >= n2 || (ii < n1 && v1[ii] > v2[jj])) {
                tmp_result[i + j] = v1[i];
                ++i;
            } else {
                tmp_result[i + j] = v2[j];
                ++j;
            }
        }
        for (; i < n1; i++) {
            tmp_result[i + j] = v1[i];
        }
        for (; j < n2; j++) {
            tmp_result[i + j] = max_num2[k - n][j];
        }
    }

    bool smaller(vector<int> &result, vector<int> &tmp_result) {
        int i;
        for (i = 0; i < result.size() && result[i] == tmp_result[i]; i++)
            ;
        if (i < result.size() && result[i] < tmp_result[i])
            return true;
        return false;
    }
};

int main() {

	Solution s;

	return 0;
}
