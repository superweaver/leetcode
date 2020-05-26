#include "common.h"

class Solution {
  public:
    // https ://www.cnblogs.com/grandyang/p/6680548.html
    int findLUSlength(vector<string> &strs) {
        // string of longer length is in front of new vector
        sort(strs.begin(), strs.end(), [](const string &a, const string &b) {
            if (a.size() == b.size()) {
                return a > b;
            } else {
                return a.size() > b.size();
            }
        });
        unordered_set<string> cache;
        int n = strs.size();
        for (int i = 0; i < n; ++i) {
            if (i == n - 1 || strs[i] != strs[i + 1]) {
                // only handle the last one for repeated string
                // check if strs[i] is the LPS
                // if found, return its length
                bool found = true;
                string &candidate = strs[i];
                for (auto &s : cache) {
                    size_t j = 0;
                    for (auto c : s) {
                        if (j < candidate.size() && c == candidate[j]) {
                            j++;
                        }
                    }
                    if (j == candidate.size()) {
                        // candidate is a subsequence of s, no need to continue
                        found = false;
                        break;
                    }
                }
                if (found) {
                    return candidate.size();
                }
            }
            cache.insert(strs[i]); // even insert repeated string
        }
        return -1;
    }
};

int main() {

    Solution s;

    return 0;
}
