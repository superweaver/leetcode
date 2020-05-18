#include "common.h"
// https://leetcode.com/problems/isomorphic-strings/discuss/57796/My-6-lines-solution
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }
        vector<int> ms(128, -1); // char and last index of char
        vector<int> mt(128, -1);
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            // check if the last index of s[i] and t[i]
            // are same
            // note initially, all are -1, same
            if (ms[s[i]] != mt[t[i]]) {
                return false;
            }
            ms[s[i]] = i;
            mt[t[i]] = i;
        }
        return true;
    }
};

int main() {

	Solution s;

	return 0;
}
