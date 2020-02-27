#include "common.h"
class Solution {
public:
    int balancedString(string s) {
        vector<int> count(128, 0);
		int n = s.size();
		int targetLen = n >> 2;
		int left = 0;
		for (; left < n; ++left) {
			count[s[left]]++;
			if (count[s[left]] > targetLen) {
                count[s[left]]--;
                left--;
				break;
            }
		}
		if (left == n) {
			return 0;
		}
		int right = n - 1;
		for (; right > left; --right) {
			count[s[right]]++;
			if (count[s[right]] > targetLen) {
				count[s[right]]--;
				right++;
				break;
			}
		}
		int result = right - left - 1;
		while (left >= 0) {
			// decrease left by one?		
			count[s[left]]--;
			--left;
			while(right > left) {
				--right;
				count[s[right]]++;
				if (count[s[right]] > targetLen) {
					count[s[right]]--;
					right++;
					break;
                }
            }
            result = min(result, right - left - 1);
        }
		return result;
    }
};

int main() {
    string s = "QWER"; // 0
    s = "QQWE"; // 1
    s = "QQQW"; // 2
    s = "QQQQ"; // 2
    Solution so;
	cout << so.balancedString(s) << endl;

	return 0;
}
