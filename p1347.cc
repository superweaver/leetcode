#include "common.h"
class Solution {
public:
    int minSteps(string s, string t) {
		vector<int> count(128, 0);
		for(auto c : s) {
			count[c]++;
		}
		for(auto c : t) {
			count[c]--;
		}
		int diff = 0;
		for (char c = 'a'; c <= 'z'; ++c) {
			diff += abs(count[c]);
		}
		return diff >> 1;
    }
};

int main() {
    string s = "bab";
	string t = "aba"; // 1
	s = "leetcode", t = "practice"; // 5
	s = "anagram", t = "mangaar"; //0
	s = "xxyyzz", t = "xxyyzz"; // 0
	s = "friend", t = "family"; //4
    Solution so;
	cout << so.minSteps(s, t) << endl;

	return 0;
}
