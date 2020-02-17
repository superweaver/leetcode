#include "common.h"
class Solution {
public:
    string smallestSubsequence(string text)
    {
		// from leetcode solutions
		vector<int> freq(256, 0);
        for (auto c : text) {
            freq[(int)c]++;
        }
		vector<bool> visited(256, false);
        string s;
        for (auto c : text) {
            if (visited[(int)c]) {  // this has been put into s; this c won't be "better" than previous c
                --freq[(int)c];     // update frequence
                continue;
            };
            // !!! c is better than s.back(), and there are more s.back()
            while ((!s.empty()) && (c < s.back()) && (freq[(int)s.back()])) {
                visited[(int)s.back()] = false; // !!
                s.pop_back();
            }
			// put it into s temporarily
			s.push_back(c);
            --freq[(int)c]; 
            visited[(int)c] = true; // set flag
        }
        return s;
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

int main()
{
    string str = "cdadabcc";  // adbc
    str = "abcd";             // abcd
    str = "ecbacba";
    str = "leetcode";              // letcod
    str = "cbaacabcaaccaacababa";  // abc
    Solution s;
    cout << s.smallestSubsequence(str) << endl;
    return 0;
}
