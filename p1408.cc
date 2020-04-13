#include "common.h"
class Solution {
   public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> result;
        for (size_t i = 0; i < words.size(); ++i) {
            for (size_t j = 0; j < words.size(); ++j) {
                if (i == j) {
                    continue;
                }
                if (words[j].find(words[i]) != string::npos) {
                    result.push_back(words[i]);
                    break;
                }
            }
        }
        return result;
    }
};

int main() {
    vector<string> words = {"leetcode", "et", "code"};
    Solution s;
    displayvector(s.stringMatching(words));
    return 0;
}
