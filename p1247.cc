#include "common.h"
class Solution {
public:
    int minimumSwap(string s1, string s2) {
		int n = s1.size();
		int xy = 0;
		int yx = 0;
		for (int i = 0; i < n; ++i) {
			if (s1[i] != s2[i]) {
				if (s1[i] == 'x') {
					xy++;
				} else {
					yx++;
				}
			}
		}
		if (xy < yx) {
			swap(xy, yx);
		}
		// xy >= yx
		// s1: xxxxyy
		// s2: yyyyxx
		// xy = 4, yx = 2
		// return 2 + 1
		// s1: xxxyyy
		// s2: yyyxxx
		// return 1 + 1 + 2
		if ((xy + yx) & 1) {
			return -1;
		} else {
            return xy / 2 + yx / 2 + ((xy & 1) ? 2 : 0);
        }
    }
};

int main() {

    string s1 = "xx", s2 = "yy"; // 1
    s1 = "xy", s2 = "yx";        // 2
    s1 = "xx", s2 = "xy";        // -1
    s1 = "xxyyxyxyxx", s2 = "xyyxyxxxyx";
    Solution s;
    cout << s.minimumSwap(s1, s2) << endl;
    return 0;
}
