#include "common.h"
class Solution {
public:
    int maxRepOpt1(string text) {
		vector<int> count(128, 0);
		vector<int> last(128, -1);
		for (auto c : text) {
			count[c]++;
		}
		int n = text.size();
		int result = 0;
		for (int i = 0; i < n;) {
			// i is start of block
			char c = text[i];
            int j = i + 1;
			if (last[c] >= j) {
				j = last[c] + 1;
			} else {
                while (j < n && text[j] == c) {
                    j++;
                }
                last[c] = j - 1;
            }
			int blocksize = j - i;
			if (result > count[text[i]]) {
				i = j;
			} else {
				if (blocksize == count[c]){
					// impossible to get any 'c'
					result = max(result, blocksize);
				} else {
					if (j == n) { // special case
						result = max(result, blocksize);
					} else {
                        // it is possible to get at least one more 'c'
                        int right = 0;
                        for (int k = j + 1; k < n; ++k) {
                            if (text[k] != c) {
                                break;
                            } else {
                                right++;
								last[c] = k;
                            }
                        }
						// it is possible the borrowed one is from the right block;
                        result = max(result, min(blocksize + 1 + right, count[c]));  // !!!
                    }
                }
                i = j;
            }
		}
		return result;
    }
};

int main() {

	string text = "ababa"; // 3
	text = "aaabaaa"; // 6
	text = "aaabbaaa"; // 4
	text = "aaaaa"; // 5
	//text = "abcdef"; // 1
	Solution s;
	cout << s.maxRepOpt1(text) << endl;
	return 0;
}
