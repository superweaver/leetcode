#include "common.h"
// https://leetcode.com/problems/permutation-in-string/discuss/638531/Java-or-C%2B%2B-or-Python3-or-Detailed-explanation-or-O(N)-time
class Solution {
  public:
    bool checkInclusion(string s1, string s2) {
        int map[128] = {0};
        for (char c : s1) {
            map[c - 'a']++;
        }
        int j = 0;
        int i = 0;
        int unmatched = s1.size();
        while (j < s2.size()) {
            // nice trick
            if (map[s2[j++]]-- > 0) {
                unmatched--;
            }

            if (unmatched == 0) {
                return true;
            }

            // nice trick
            if (j - i == s1.size() && map[s2[i++]]++ >= 0) {
                unmatched++;
            }
        }
        return false;
    }
};

int main() {

	Solution s;

	return 0;
}
