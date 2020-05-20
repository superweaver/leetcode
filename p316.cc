#include "common.h"

class Solution {
public:
    //http://www.cnblogs.com/grandyang/p/5085379.html
    string removeDuplicateLetters(string s) {
        int m[256] = {0}; // m is used to count char
        int visited[256] = {0};// mark if char is alreay in output string
        string res = "0"; // a trick here
        // '0' > ['a'-'z' 'A'-'Z']
        // count
        for (auto a : s) {
            ++m[a];
        }

        for (auto a : s) {
            --m[a];              // minus one first;
            if (visited[a]) continue;
            // visited[a] is 0
            while (a < res.back() && m[res.back()]) {
                // a < res.back() && m[res.back()]
                // means there are at least one more res.back() on the right side.
                // a < res.back() means we should put a before res.back().
                // and mark res.back() as unvisited
                visited[res.back()] = 0;
                res.pop_back();
            }
            res += a;
            visited[a] = 1;
        }
        return res.substr(1);
    }
};


class Solution_hai {
public:
    string smallestSubsequence_hai(string text)
    {
        // my solution
        int n = text.size();
        vector<int> cache(n, 0);
        unordered_set<char> who;
        for (int i = n - 1; i >= 0; --i) {
            who.insert(text[i]);
            cache[i] = who.size();
        }
        string result;
        int index = -1;

        while (!who.empty()) {
            result.push_back('z' + 1);
            for (size_t i = 0; i < text.size(); ++i) {
                if (cache[i] == (int)who.size()) {
                    if (text[i] < result.back()) {  // can't be <=
                        result.back() = text[i];
                        index = i;
                    }
                } else {
                    break;
                }
            }
            string next;
            for (size_t j = index + 1; j < text.size(); ++j) {
                if (text[j] != result.back()) {
                    next.push_back(text[j]);
                }
            }
            next.swap(text);
            cache = vector<int>(text.size(), 0);
            who.clear();
            for (int i = text.size() - 1; i >= 0; --i) {
                who.insert(text[i]);
                cache[i] = who.size();
            }
        }
        return result;
    }
};


int main() {

	Solution s;

	return 0;
}
