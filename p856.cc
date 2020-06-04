#include "common.h"

class Solution {
public:
    int scoreOfParentheses(string S) {
        stack<int> left;
        int n = S.size();
        vector<int> match(n, 0);
        for(int i = 0; i < n; ++i) {
            if(S[i] == '(') {
                left.push(i);
            } else {
                auto last = left.top();
                left.pop();
                match[last] = i;
                match[i] = last;
            }
        }
        return helper(S, 0, n-1, match);
    }
private:
    int helper(const string& S, int start, int end, const vector<int>& match)
    {
        if(end == start + 1) return 1;
        if(end == match[start]) {
            return 2 * helper(S, start + 1, end-1, match);
        }
        else {
            int mid = match[start];
            return helper(S, start, mid, match) + helper(S, mid + 1, end, match);
        }
    }
};


int main() {

	Solution s;

	return 0;
}
