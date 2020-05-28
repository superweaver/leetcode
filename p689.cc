#include "common.h"
// https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/discuss/108231/C%2B%2BJava-DP-with-explanation-O(n)
class Solution {
  public:
    vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
        int n = nums.size(), maxsum = 0;
        vector<int> sum = {0}, posLeft(n, 0), posRight(n, n - k), ans(3, 0);
        for (int i : nums) {
            sum.push_back(sum.back() + i);
        }
        // DP for starting index of the left max sum interval
        for (int i = k, tot = sum[k] - sum[0]; i < n; i++) {
            if (sum[i + 1] - sum[i + 1 - k] > tot) { // > !!!
                posLeft[i] = i + 1 - k;
                tot = sum[i + 1] - sum[i + 1 - k];
            } else
                posLeft[i] = posLeft[i - 1];
        }
        // DP for starting index of the right max sum interval
        // caution: the condition is ">= tot" for right interval, and "> tot" for left interval
        for (int i = n - k - 1, tot = sum[n] - sum[n - k]; i >= 0; i--) {
            if (sum[i + k] - sum[i] >= tot) { // >= nice
                posRight[i] = i;
                tot = sum[i + k] - sum[i];
            } else
                posRight[i] = posRight[i + 1];
        }
        // test all possible middle interval
        for (int i = k; i <= n - 2 * k; i++) {
            int l = posLeft[i - 1], r = posRight[i + k];
            int tot = (sum[i + k] - sum[i]) + (sum[l + k] - sum[l]) + (sum[r + k] - sum[r]);
            if (tot > maxsum) {
                maxsum = tot;
                ans = {l, i, r};
            }
        }
        return ans;
    }
};

class Solution_my {
public:
	vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
		int n = nums.size();

		vector<int> ksum;
		int sum = 0;
		for (int i = 0; i < n; ++i) {
			if (i < k) {
				sum += nums[i];
				if (i == k - 1) {
					ksum.push_back(sum);
				}
			}
			else {
				int next = ksum.back() - nums[i - k] + nums[i];
				ksum.push_back(next);
			}
		}
		// [1, 2, 1, 2, 6, 7, 5, 1]
		//	k = 2;
		// ksum = [3, 3, 3, 8, 13, 12, 6]
		// ksum.size() == n - k + 1
		int len = ksum.size();
		vector<int> dp1(len, 0);	// up to ith block, the max sum you can get by picking only one subarray;
		dp1[0] = ksum[0];
		for (int i = 1; i < len; ++i) {
			dp1[i] = max(ksum[i], dp1[i - 1]);
		}
		len -= k;
		vector<int> dp2(len, 0);
		// i in dp2 corrsponding to i+k in dp1
		dp2[0] = ksum[0] + ksum[k];
		for (int i = 1; i < len; ++i) {
			dp2[i] = max(dp2[i - 1], ksum[i + k] + dp1[i]);
		}
		len -= k;
		vector<int> dp3(len, 0);
		// i in dp3 is i+k in dp2, i + 2k in dp1
		dp3[0] = ksum[0] + ksum[k] + ksum[k + k];
		for (int i = 1; i < len; ++i) {
			dp3[i] = max(dp3[i - 1], ksum[i + k + k] + dp2[i]);
		}
		int r = INT_MIN;
		for (auto i : dp3) {
			r = max(r, i);
		}
		vector<int> result;
		for (int i = 0; i < len; i++) {
			if (dp3[i] == r) {
				r -= ksum[i + 2 * k];
				result.push_back(i + 2 * k);
				break;
			}
		}
		len += k;
		for (int i = 0 ; i < len; i++) {
			if (dp2[i] == r) {
				r -= ksum[i + k];
				result.push_back(i + k);
				break;
			}
		}
		len += k;
		for (int i = 0; i < len; i++) {
			if (dp1[i] == r) {
				r -= ksum[i];
				result.push_back(i);
			}
		}
		reverse(result.begin(), result.end());

		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
