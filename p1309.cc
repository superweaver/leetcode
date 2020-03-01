#include "common.h"
//1309. Decrypt String from Alphabet to Integer Mapping
class Solution {
public:
    string freqAlphabets(string s) {
        int n = s.size();
        string result;
        for (int i = 0; i < n; ++i){
            if (s[i]=='#') {
                result.pop_back();
                result.pop_back();
                int d = (s[i-2]- '0')*10 + s[i-1] - '0';
                result.push_back(d-1 + 'a');
            } else {
                result.push_back(s[i]-'1' + 'a');
            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
