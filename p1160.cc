#include "common.h"
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
		vector<int> count(128, 0);
		for( char c : chars) {
			count[c]++;
		}
		int result = 0;
		for (auto & s : words) {
			result += helper(s, count);
		}
		return result;
    }
private:
	int helper(const string& s, const vector<int>& count) {
		vector<int> scount(128, 0);
		for (auto c : s) {
			scount[c]++;
			if (scount[c] > count[c]) {
				return 0;
			}
		}
		return s.size();
	}
};

int main() {
	vector<string> words = {"cat","bt","hat","tree"};
	string chars = "atach"; // 6
	words = {"hello","world","leetcode"}, chars = "welldonehoneyr"; // 10
	
	Solution s;
	cout << s.countCharacters(words, chars) << endl;
	return 0;
}
