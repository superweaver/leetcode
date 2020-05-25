#include "common.h"
class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int i = 1;
        size_t pos = 0;
        sentence.push_back(' ');
        while(true) {
            auto next = sentence.find(' ', pos);
            if (next == string::npos) {
                break;
            }
            auto substr = sentence.substr(pos, next);
            if (substr.find(searchWord) == 0) {
                return i;
            }
            pos = next + 1;
            i++;
        }
        return -1;
    }
};

int main() {

    string searchWord = "burger";
    string sentence = "i love eating burger";
    Solution s;
    cout << s.isPrefixOfWord(sentence, searchWord) << endl;

    return 0;
}
