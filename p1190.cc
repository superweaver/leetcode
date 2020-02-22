#include "common.h"
class Solution {
public:
    string reverseParentheses(string s) {
		int n = s.size();
		int p = 0;
		vector<int> match(n, -1);
		vector<int> chars(n, 0);
		stack<int> stk;
		int count = 0;
		for (int i = 0; i < n; ++i) {
			if (s[i] == '(') {
				stk.push(i);
			}
			else if (s[i] == ')') {
				match[i] = stk.top();
				match[stk.top()] = i;
				stk.pop();
				p += 2;
			} else {
				count++;
			}
			chars[i] = count;
		}
		int m = n - p;
		string result(m, '0');
		int ri = 0;
		int rj = m - 1;
		bool flip = false;
		int i = 0;
		int j = n - 1;
		helper(result, ri, rj, s, i, j, flip, match, chars);
		/*
		while(i <= j) {
			if (flip) {
                while (i <= j && s[i] != '(') {
                    result[rj--] = s[i++];
                }
                while (i <= j && s[j] != ')') {
                    result[ri++] = s[j--];
                }
				i++;
				j--;
				flip = !flip;
            } else {
                while (i <= j && s[i] != '(') {
					result[ri++] = s[i++];
				}
				while(i <= j && s[j] != ')') {
					result[rj--] = s[j--];
				}
				i++;
				j--;
				flip = !flip;
			}
		}
		*/
		return result;
    }
private:
	void helper(string& result, int rstart, int rend, string s, int sstart, int send, bool flip, vector<int>& match, vector<int>&chars) {
        if (rend - rstart + 1 <= 0) {
            return;
		}
        while (rstart <= rend) {
			if (!flip) {
				while(sstart <=send && s[sstart] != '(') {
                    result[rstart++] = s[sstart++];
				}
				if (sstart <= send) {
				// s[sstart] == '('
					int end = match[sstart];
					int fills = chars[end] - chars[sstart];	
					helper(result, rstart, fills + rstart - 1, s, sstart + 1, end - 1, !flip, match, chars);
					rstart += fills;
					sstart = end + 1;
                }
            } else{
				while(sstart <=send && s[send] != ')') {
					result[rstart++] = s[send--];
				}
				if (sstart <= send) {
					// s[send] == ')'
					int start = match[send];
					int fills = chars[send] - chars[start];
					helper(result, rstart, fills + rstart - 1, s, start + 1, send - 1, !flip, match, chars);
					rstart+=fills;
					send = start - 1;
				}
			}
		}
	}
};

int main() {

    string s = "(abcd)"; // dcba
	s = "(u(love)i)"; // iloveu
	s = "(ed(et(oc))el)"; // leetcode
	s = "a(bcdefghijkl(mno)p)q"; // apmnolkjihgfedcbq
	s= "ta()usw((((a))))"; //"tauswa"
    Solution so;
	cout << so.reverseParentheses(s) << endl;
	return 0;
}
