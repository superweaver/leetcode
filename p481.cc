#include "common.h"
//https://www.cnblogs.com/grandyang/p/6286540.html
class Solution {
public:
	int magicalString(int n) {
		// generate magical string and count
        if (n <= 0) {
            return 0;
        }
        if (n <= 3) {
            return 1;
        }
        string s = "122";
        string base("21");
        int index = 1;
        char c = base[index];  // == 1

		int head = 2; // to get how many '1' or '2' to fill at tail and later
		int tail = 3;

		int result = 1;
		while (tail < n) {
			// fill s[head] character c at tail and later
			// and then flip c '1'->'2'->'1'
			int terms = s[head] - '0';
			s.append(terms, c);
			tail += terms;
			if (tail >= n) {
				if (c == '1') {
					result += terms - (tail - n);
					return result;
				}
				else { // c == '2'
					return result;
				}
			}
			else {
				if (c == '1') {
					result += terms;
				}
			}
			head++;

			// flip char c !!!
			index++;
			index &= 0x01;
			c = base[index];
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
