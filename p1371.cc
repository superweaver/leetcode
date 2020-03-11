#include "common.h"
//1371. Find the Longest Substring Containing Vowels in Even Counts
class Solution {
public:
	int findTheLongestSubstring(string s) {
		string vowels = "aeiou";
		int mask = 0;
		for (auto c : vowels) {
            mask |= (1 << (c - 'a'));
        }
		unordered_map<int, int> count2index;
		count2index[0] = -1;
		int result = 0;
		int n = s.size();
		int prefix = 0;
		for (int i = 0; i < n; ++i) {
            prefix ^= (1 << (s[i] - 'a'));
            prefix &= mask;
            if (count2index.count(prefix)) {
                result = max(result, i - count2index[prefix]);
            } else {
                count2index[prefix] = i;
            }
        }
		return result;
    }
};

int main() {
	string s = "eleetminicoworoep"; // 13
	s = "leetcodeisgreat"; // 5
	s = "bcbcbc"; // 6
	Solution so;
	cout << so.findTheLongestSubstring(s) << endl;
	return 0;
}
