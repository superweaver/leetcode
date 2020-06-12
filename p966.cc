#include "common.h"
class Solution {
public:
	vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
		unordered_set<string> wordset(wordlist.begin(), wordlist.end());
		unordered_map<string, int> cap_map;
		unordered_map<string, int> vowel_map;
		string vowels = "aeiou";
		vector<bool> flag(128, false);
		for (auto c : vowels) {
			flag[c] = true;
		}
		for (size_t i = 0; i < wordlist.size(); ++i) {
			string s = wordlist[i];
			for (auto &c : s) {
				if (c >= 'A' && c <= 'Z') {
					c += 'a' - 'A';
				}
			}
			if (!cap_map.count(s)) {
				cap_map[s] = i;
			}
			for (auto&c : s) {
				if (flag[c]) {
					c = 'a';
				}
			}
			if (!vowel_map.count(s)) {
				vowel_map[s] = i;
			}
		}
		vector<string> result;
		for (auto&q : queries) {
			if (wordset.count(q)) {
				result.push_back(q);
			}
			else {
				string s = q;
				for (auto &c : s) {
					if (c >= 'A' && c <= 'Z') {
						c += 'a' - 'A';
					}
				}
				if (cap_map.count(s)) {
					result.push_back(wordlist[cap_map[s]]);
					continue;
				}
				for (auto&c : s) {
					if (flag[c]) {
						c = 'a';
					}
				}
				if (vowel_map.count(s)) {
					result.push_back(wordlist[vowel_map[s]]);
						continue;
				}
				result.push_back("");
			}
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
