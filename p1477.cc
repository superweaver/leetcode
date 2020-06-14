#include "common.h"
class Solution {
  public:
    int minSumOfLengths(vector<int> &arr, int target) {
        int n = arr.size();
        const int INF = INT_MAX / 2;
        vector<int> prefix_sum(n + 1, 0);
        vector<int> left_len(n + 1, INF);
        for (int i = 0; i < n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + arr[i];
            auto end = prefix_sum.begin() + i + 2;
            auto it = lower_bound(prefix_sum.begin(), end,
                                  prefix_sum[i + 1] - target);
            if (it != end && *it == prefix_sum[i + 1] - target) {
                left_len[i + 1] = min(left_len[i], (int)distance(it, end) - 1);
            } else {
                left_len[i + 1] = left_len[i];
            }
        }
        vector<int> suffix_sum(n + 1, 0);
        vector<int> right_len(n + 1, INF);
        int r = INT_MAX;
        for (int i = n - 1; i >= 0; --i) {
            // exclude node i;
            auto end = suffix_sum.rbegin() + (n - i);
            auto it = lower_bound(suffix_sum.rbegin(), end, suffix_sum[i + 1] - target);
            if (it != end && *it == suffix_sum[i+1] - target) {
                right_len[i] = min(right_len[i+1], (int)distance(it, end) - 1);
            }
            else {
                right_len[i] = right_len[i+1];
            }
            r = min(r, left_len[i+1] + right_len[i]);
            suffix_sum[i] = suffix_sum[i+1] + arr[i];
        }
        return r < INF ? r : -1;
    }
};

int main() {
    vector<int> arr = {3,2,2,4,3};
    int target = 3; //2
    arr = {7,3,4,7}, target = 7;// 2
    //arr = {4,3,2,6,2,3,4}, target = 6; // -1
    //arr = {5,5,4,4,5}, target = 3; // -1
    //arr = {3,1,1,1,5,1,2,1}, target = 3; // 3
    //arr = {64, 5, 20, 9, 1, 39}, target = 69; // 6

    Solution s;
    cout << s.minSumOfLengths(arr, target) << endl;

	return 0;
}
