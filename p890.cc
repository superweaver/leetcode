#include "common.h"
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern)
    {
        vector<string> result;
        for (auto& s : words) {
            if (check(s, pattern)) {
                result.push_back(s);
            }
        }
        return result;
    }

private:
    bool check(const string& str, const string& pattern)
    {
        if (str.size() != pattern.size()) {
            return false;
        }
        vector<int> s2p(128, 0);
        vector<int> p2s(128, 0);
        for (size_t i = 0; i < str.size(); ++i) {
            char s = str[i];
            char p = pattern[i];
            if (s2p[s] == 0) { // s to p map has not been set up yet
                s2p[s] = p;    // set up map
                if (p2s[p] != 0) { // p2s has been set up, fail
                    return false;
                } else {
                    p2s[p] = s; // set up p2s map
                }
            } else { // there is s2p map, check if p is the correct one
                if (p != s2p[s]) {
                    return false;
                }
            }
        }
        return true;
    }
};



int main() {

	Solution s;

	return 0;
}
