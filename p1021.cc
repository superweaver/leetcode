#include "common.h"
class Solution {
public:
    string removeOuterParentheses(string S) {
        stack<int> s;
        string r;
        for(size_t i = 0; i < S.size(); ++i){
            if(S[i] == '('){
                s.push(i);
            } else {
                int last = s.top();
                s.pop();
                if(s.empty()){  
                    // nice trick
                    r += S.substr(last + 1, i - last - 1);
                }
            }
        }
        return r;
    }
};

int main() {

	Solution s;

	return 0;
}
