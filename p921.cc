#include "common.h"

class Solution {
public:
    int minAddToMakeValid(string S) {
        int left = 0;
        int right = 0;
        for(auto c:S){
            if(c=='('){
                left++;
            } else{
                if(left) { // left > 0
                    left--;
                } else {
                    right++;
                }
            }
        }
        return left + right;// they are left in stack;
    }
};

int main() {

	Solution s;

	return 0;
}
