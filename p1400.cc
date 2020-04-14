#include "common.h"
class Solution {
public:
    bool canConstruct(string s, int k) {
		if ((int)s.size() < k) {
			return false;
		}
		vector<int> counter(128, 0);
		for(auto c : s) {
			counter[c]++;
		}
		int pairs = 0;
		int odds = 0;
		for (char c = 'a' ; c <= 'z'; ++c) {
			if (counter[c]) {
                pairs += (counter[c] >> 1);
                odds += (counter[c] & 1);
                if (odds > k) {
					return false;
				}
			}
		}
		// pairs can be used as a pair or two separate elements
        return (2 * pairs) >= k - odds;
    }
};

int main() {
    string s = "annabelle";
	int k = 2; // true
	s = "leetcode", k = 3; // false
	s = "true", k = 4; // !!!!
	s = "yzyzyzyzyzyzyzy", k = 2;
	s = "cr", k = 7;
    s = "qlkzenwmmnpkopu", k = 15;

    Solution so;
    cout << so.canConstruct(s, k) << endl;

    return 0;
}
