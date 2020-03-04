#include "common.h"
class Solution {
public:
    string breakPalindrome(string palindrome) {
        int n = palindrome.size();
        if (n == 1){
            return {};
        }
        // n >= 2
        for (int i = 0, j = n - 1; i < j; ++i, --j){
            if (palindrome[i]!='a'){
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        // all 'a' or 'aaaxaaa'
        // puth last letter to 'b'
        palindrome.back() = 'b';
        return palindrome;
    }
};

int main() {

	string str("a"); // {}
    str = "aa";      // ab
    str = "axa";     // axb
    Solution s;
	cout << s.breakPalindrome(str) << endl;
    return 0;
}
