#include "common.h"
class Solution {
    // https://zxi.mytechroad.com/blog/hashtable/leetcode-525-contiguous-array/
  public:
    int findMaxLength(vector<int> &nums) {
        // prefixsum = sum((nums[0...i] << 1 - 1)
        // unordered_map<int, size_t> cache; // prefix -> end of segments
        int n = nums.size();
        vector<int> cache(2 * n + 1, INT_MIN); // 0...n-1 is used for prefix sum
        // j = n...2*n is used to store first index x where prefix_sum[x] == j-n
        cache[n] = -1; // trick // prefix sum == 0;
        size_t result = 0;
        int sum = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            sum += (nums[i] << 1) - 1; // trick
            int index = sum + n;
            if (cache[index] != INT_MIN) { // trick
                // prefixsum from cache[index] + 1 to i is zero
                result = max(result, i - cache[index]);
            } else {
                cache[index] = i; // first apperance
            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
