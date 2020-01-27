#include "common.h"
class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
       // greedy 
       // https://zxi.mytechroad.com/blog/greedy/leetcode-936-stamping-the-sequence/
       // https://www.jianshu.com/p/cb4cbd11511b
       // https://www.youtube.com/watch?v=TFL6mx9Gbqo&feature=share
       // https://leetcode.com/articles/stamping-the-sequence/#
       int ns = stamp.size(), nt = target.size();
       vector<int> seq;
        auto pos = target.find(stamp);
        if (pos == string::npos) {
            return {};
        } else {
            seq.push_back(pos);
            std::fill(target.begin() + pos, target.begin() + pos + ns, '?');
        }
        vector<bool> visited(nt, false);
        visited[pos] = true;
        int matchedChars = ns;
        while(matchedChars < nt) {
            bool foundmatch = false;
            for (int i = 0; i + ns <= nt; ++i) {
                if (visited[i]) continue;
                int match = helper(i, target, stamp);
                if (!match) continue;
                visited[i] = true;
                matchedChars += match;
                seq.push_back(i);
                foundmatch = true;
            }
            if (!foundmatch) {
                return {};
            }
        }
        reverse(seq.begin(), seq.end());
        return seq;
    }
private:
    int helper(int start, string& target, const string& stamp) {
        // return number of chars in stamp that are match in substr of target, staring at start
        int match = stamp.size();
        int end = start + stamp.size();
        for (int i = start, j = 0; i < end; ++i, ++j) {
            if (target[i] == '?') {
                match--;
            } else if (target[i] != stamp[j]) {
                return 0;
            }
        }

        if (match) {
            std::fill(target.begin() + start, target.begin() + end, '?');
        }
        return match;
    }
};
int main() {
    string stamp = "abc", target = "ababc";
    stamp = "abca", target = "aabcaca";
    Solution s;
    displayvector(s.movesToStamp(stamp, target));
    return 0;
    
}
