#include "common.h"
class Solution {
public:
    vector<string> printVertically(string s) {
		s.push_back(' ');
		size_t maxLen = 0;
		size_t n = 0;
		size_t pre = 0;
		vector<string> cache;
        while (true) {
            auto next = s.find_first_of(' ', pre);
            cache.push_back(s.substr(pre, next - pre));
            maxLen = max(maxLen, cache.back().size());
			n++;
			pre = next + 1;
            if (pre >= s.size()) {
                break;
            }
        }
        vector<string> result(maxLen, string(n, ' '));
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < maxLen; ++j) {
				if(j < cache[i].size()) {
					result[j][i] = cache[i][j];
				}
			}
		}
		for(auto&s:result) {
			while(!s.empty() && s.back()==' '){
				s.pop_back();
			}
		}
		return result;
    }
};

int main() {
    string s = "HOW ARE YOU";
    s = "TO BE OR NOT TO BE";
    s = "CONTEST IS COMING";
    Solution so;
    displayvector(so.printVertically(s));
    return 0;
}
