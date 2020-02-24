#include "common.h"
class Solution {
public:
    string removeDuplicates(string s, int k) {
		vector<int> cache;
		for (auto c : s) {
            if (cache.empty()) {
				cache.push_back(((int)c << 16) + 1);
            } else {
				auto& last = cache.back();
				if ((int)c != (last >> 16)) {
					cache.push_back(((int)c << 16) + 1);
				} else {
					last++;	
					if ((last&0xFFFF) == k) {
						cache.pop_back();
					}
				}
			}
        }
		string result;
		for (auto i : cache) {
            result += string(i & 0xFFFF, char(i >> 16));
        }
		return result;
    }
};

int main()
{
    string s = "abcd";
    int k = 2; // abcd
	s = "deeedbbcccbdaa", k = 3; // aa
	s = "pbbcggttciiippooaais", k = 2; // ps
    Solution so;
	cout << so.removeDuplicates(s, k) << endl;
	

	return 0;
}
