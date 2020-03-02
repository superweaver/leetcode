#include "common.h"
class Solution {
public:
    int removePalindromeSub(string s) {
        if (s.empty()) return 0;
        int n = s.size();
        bool isPalindrome = true;
        for (int i = 0, j = n - 1; i < j; ++i, --j){
            if (s[i] != s[j]){
                isPalindrome = false;
                break;
            }
        }
        if (isPalindrome){
            return 1;
        } else {
            return 2;
        }
    }
};

int main() {

	Solution s;

	return 0;
}
