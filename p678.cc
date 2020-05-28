#include "common.h"
class Solution {
public:
    bool checkValidString(string s) {
        stack<int> left, star; // store the index of left parenthesis and star
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == '*') {
                star.push(i);
            } else if (s[i] == '(') {
                left.push(i);
            } else {
                if (left.empty() && star.empty()) {
                    return false;
                }
                if (!left.empty()) {
                    left.pop();
                }
                else {
                    star.pop();
                }
            }
        }

        while (!left.empty() && !star.empty()) {
            // star wil act as right parenthesis
            // but ) but appear after (
            if (left.top() > star.top()) {
                return false; // so good
            }
            left.pop();
            star.pop();
        }
        return left.empty();
    }
};

class Solution_huahua {
    // http://zxi.mytechroad.com/blog/dynamic-programming/leetcode-678-valid-parenthesis-string/
public:
    bool checkValidString(const string& s) {
        // counting method
        int min_op = 0; // minimum number of possible left parenthesis
        int max_op = 0; // maximum number of possible left parenthesis, set all left * to left parenthesis
        // max_op >= 0, otherwise, right parenthesis is more
        // if (min_op < 0) reset to 0
        for (auto c:s){
            if (c == '('){
                min_op++;
                max_op++;
            } else if (c == ')'){
                min_op--;
                max_op--;
            } else { // c = '*'
                max_op++;   // * -> (
                min_op--;   // * -> )
            }
            if (min_op < 0){
                min_op = 0;
            }
            if (max_op < 0) {  // too many )
                return false;
            }
        }
        return min_op == 0;
    }
};

class Solution_huahua2 {
    // http://zxi.mytechroad.com/blog/dynamic-programming/leetcode-678-valid-parenthesis-string/
public:
    bool checkValidString(const string& s) {
        int l = s.length();
        if (l == 0) return true;
        vector<vector<int>> dp(l, vector<int>(l, 0));
        for (int i = 0; i < l; ++i)
            if (s[i] == '*') dp[i][i] = 1;  // base case
        for (int len = 2; len <= l; ++len)
            for (int i = 0; i <= l - len; ++i) {
                int j = i + len - 1;
                // (...), *...), (...*, *...*
                if ((s[i] == '(' || s[i] == '*')
                  &&(s[j] == ')' || s[j] == '*'))
                    if (len == 2 || dp[i + 1][j - 1]) {
                        dp[i][j] = 1;
                        continue;
                    }

                for (int k = i; k < j; ++k) // set break point
                    if (dp[i][k] && dp[k + 1][j]) {
                        dp[i][j] = 1;
                        break;  // if found one, no need to continue
                    }
            }
        return dp[0][l - 1];
    }
};
class Solution_my {
public:
	bool checkValidString(string s) {
		string stk;
		// remove some valid parenthesis
		removeparenthesis(s);
		if (s.empty()) return true;
		if (s[0] == ')' || s.back() == '(') return false;
		int n = s.size();
		int totalleft = 0;
		int totalright = 0;
		for (auto c : s) {
			if (c == ')') {
				totalright++;
			}
			if (c == '(') {
				totalleft++;
			}
		}
		int totalstars = n - totalleft - totalright;
		stk.clear();
		return dfs(s, 0, stk, s.size(), totalleft, totalright, totalstars);
	}
private:
	void removeparenthesis(string&s) {
		string r;
		for (auto c : s) {
			if (c == ')') {
				if (!r.empty() && r.back() == '(') {
					r.pop_back();
					continue;
				}
				else {
					r.push_back(c);
				}
			}
			else {
				r.push_back(c);
			}
		}
		s.swap(r);
	}
	bool dfs(string&s, int start, string stk, int n, int left, int right, int stars) {
		if (left > right + stars || right > left + stars) {
			return false;
		}

		if (start == n) {
			return stk.empty();
		}

		char c = s[start];
		if (c == '(') {
			stk.push_back(c);
			return dfs(s, start + 1, stk, n, left, right, stars);
		}
		else if (c == ')') {
			if (stk.empty()) {
				return false;
			}
			else {
				stk.pop_back();
				return dfs(s, start + 1, stk, n, left, right, stars);
			}
		}
		else {
			// c == '*'
			c = '(';
			stk.push_back(c);
			if (dfs(s, start + 1, stk, n, left+1, right, stars-1)) {
				return true;
			}
			stk.pop_back();

			c = ')';
			if (!stk.empty()) {
				stk.pop_back(); // pop a (
				if (dfs(s, start + 1, stk, n, left, right+1, stars-1)) {
					return true;
				}
				stk.push_back('('); // key !!
			}
			// use as empty string
			if (dfs(s, start + 1, stk, n, left, right, stars-1)) {
				return true;
			}
			return false;
		}
	}
};

int main() {

	Solution s;

	return 0;
}
