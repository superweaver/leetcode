#include "common.h"
class Solution {
public:
    int longestDecomposition(string text) {
		int n = text.size();
        int result = 0;
        int left = 0;
		int right = n - 1;
		vector<int> count_lr(128, 0);
		int pre_left = -1;
		// corner case : "a" -> 1
		while(left <= right) {
            count_lr[text[left]]++;
            count_lr[text[right]]--;
			bool check = true;
			for (int c = 'a'; c <= 'z'; ++c) {
				if (count_lr[c]) {
					check = false;
					break;
				}
			}
			if (check) {
				int len = left - pre_left;
                if (text.substr(pre_left + 1, len) == text.substr(right, len)) {
					pre_left = left;
                    result += (left < right) ? 2 : 0;
                    if (right - left == 1) {
                        break;
                    }
                }
            }
			left++;
			right--;
            if (left >= right) {
                result++;
                break;
            }
        }
        return result;
    }
};

int main() {
	string text = "ghiabcdefhelloadamhelloabcdefghi"; // 7
	//text = "merchant"; // 1
	//text = "antaprezatepzapreanta"; // 11
	//text = "aaa"; // 3
	//text = "aaaa"; // 4
	text = "a"; // 1
	Solution s;
	cout << s.longestDecomposition(text) << endl;
	return 0;
}
