#include "common.h"
class Solution {
public:
    int findLUSlength(string a, string b) {
        // https://www.geeksforgeeks.org/longest-uncommon-subsequence/
        // https://www.cnblogs.com/grandyang/p/6666839.html
        // case 1: a == b, then any subsequence of a is a subsequence of b, there is no uncommon subsequence, return -1
        // case 2: a.size() == b.size(), a != b, then a is not a subsequence(b is not a subsequence of a). then return a.size() ( or b.size())
        // case 3: a.size() != b.size(), then the longer one is not a subsequence of the other, return max(a.size(), b.size());
        return a == b ? -1 : max(a.size(), b.size());
    }
};

int main() {

	Solution s;

	return 0;
}
