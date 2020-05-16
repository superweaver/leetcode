#include "common.h"
class Solution {
  public:
    int longestConsecutive(vector<int> &nums) {
        // if a number is in a consecutive elements sequence, then A+1 or A-1 must be in that
        // sequence
        size_t n = nums.size();
        if (n == 0) {
            return 0;
        }
        unordered_map<int, bool> visited;
        for (size_t i = 0; i < n; ++i) {
            visited[nums[i]] = false;
        }
        int maxLen = 1;
        for (auto it = visited.begin(); it != visited.end(); ++it) {
            if (!it->second) {
                int len = 1;
                int low = it->first;
                while (low != INT_MIN && visited.find(low - 1) != visited.end()) {
                    visited[low - 1] = true;
                    len++;
                    low--;
                }
                int high = it->first;
                while (high != INT_MAX && visited.find(high + 1) != visited.end()) {
                    visited[high + 1] = true;
                    len++;
                    ++high;
                }
                maxLen = max(len, maxLen);
            }
        }
        return maxLen;
    }
};

int main() {

	Solution s;

	return 0;
}
