#include "common.h"
class Solution {
  public:
    int maxEqualFreq(vector<int> &nums) {
        // https://leetcode.com/problems/maximum-equal-frequency/discuss/403628/Easy-Python-Solution-Concise-10-lines-Explained-O(N)

        // https://leetcode.com/problems/maximum-equal-frequency/discuss/403743/JavaC%2B%2BPython-Only-2-Cases%3A-Delete-it-or-not

        // 2 <= nums.length <= 10^5
        // 1 <= nums[i] <= 10^5
        // for element a in nums
        // count[a] means how many a has appeared in first xx elements of nums
        // freq[c] means how many different of numbers has appeared
        const int MAX_LEN = 100001;
        vector<int> count(MAX_LEN, 0);
        vector<int> freq(MAX_LEN, 0);
        int result = 1;
        int N = nums.size();
        // first n elements
        for (int n = 1; n <= N; ++n) {
            auto element = nums[n - 1];
            int count_e = count[element]; // before processing
            if (freq[count_e]) {
                --freq[count_e];
            }
            count_e = ++count[element]; // processing
            freq[count_e]++;

            if (count_e * freq[count_e] == n && n < N) {
                // then by removing next element, (n+1) is a candidate
                //  not using next element
                result = n + 1;
            }
            // using current element
            // (and count_e is not the max frequency)
            int diff =
                n - count_e * freq[count_e]; // frequency of different one, and freq[diff] must be 1
            if ((diff == count_e + 1 || diff == 1) && freq[diff] == 1) {
                result = n;
            }
        }
        return result;
    }
};

int main() {
    vector<int> nums = {2, 2, 1, 1, 5, 3, 3, 5};    //7
    nums = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5}; // 13
    //nums = {1, 1, 1, 2, 2, 2};                      // 5
    //nums = {10, 2, 8, 9, 3, 8, 1, 5, 2, 3, 7, 6};   // 8

    Solution s;
    cout << s.maxEqualFreq(nums) << endl;
    return 0;
}
