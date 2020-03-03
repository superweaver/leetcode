#include "common.h"
class Solution {
public:
    int numberOfSubstrings(string s) {
		int n = s.size();
		int total = 0;
		vector<int> count(128, 0);
		int left = 0;
        for (int right = 0; right < n; ++right) {
            count[s[right]]++;
			if (!count['a'] || !count['b'] || !count['c']) {
				continue;
			}
			// try to move left
			while(left < right) {
				if (count[s[left]] > 1) {
					count[s[left]]--;
					left++;
				} else {
					break;
				}
			}
			total += (left + 1);
        }
		return total;
    }
};

class Solution2 {
public:
    int numberOfSubstrings(string s) {
		int n = s.size();
		int total = 0;
		vector<int> count(3, 0);
		int left = 0;
        for (int right = 0; right < n; ++right) {
            count[s[right] - 'a']++;
			if (!count[0] || !count[1] || !count[2]) {
				continue;
			}
			// try to move left
			while(left < right) {
				if (count[s[left]-'a'] > 1) {
					count[s[left]-'a']--;
					left++;
				} else {
					break;
				}
			}
			total += (left + 1);
        }
		return total;
    }
};

int main() {

	string str = "abcabc"; // 10
	//str = "aaacb"; // 3
	//str = "acb"; // 1
	Solution s;
	cout << s.numberOfSubstrings(str) << endl;

	return 0;
}
