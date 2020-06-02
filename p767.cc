#include "common.h"
class Solution {
public:
	string reorganizeString(string S) {
		vector<int> count(128, 0);
		for (char c : S) {
			count[c]++;
		}
		char mostchar = 'a';
		int maxCount = -1;
		for (char c = 'a'; c <= 'z'; ++c) {
			if (maxCount < count[c]) {
				maxCount = count[c];
				mostchar = c;
			}
		}
		if (2 * maxCount >= (int)S.size() + 2) {
			return "";
		}
		else {
			vector<string> r(maxCount);
			for (int i = 0; i < maxCount; ++i) {
				r[i].push_back(mostchar);
			}
			int others = S.size() - maxCount;
			int index = 0;
			for (char c = 'a'; c <= 'z'; ++c) {
				if (c == mostchar) continue;
				if (count[c] == 0) continue;
				for (int i = 0; i < count[c]; ++i) {
					r[index++].push_back(c);
					if (index == maxCount) {
						index = 0;
					}
				}
			}
			string result;
			for (auto&s : r) {
				result += s;
			}
			return result;
		}
	}
};

int main() {

	Solution s;

	return 0;
}
