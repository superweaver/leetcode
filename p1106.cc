#include "common.h"
class Solution {
public:
    bool parseBoolExpr(string expression)  {
		int n = expression.size();
        vector<int> match(n, -INT_MAX);
		stack<int> p;
		for (int i = 0; i < n; ++i) {
			if (expression[i] == '(') {
				p.push(i);
			} else if (expression[i] == ')') {
				match[i] = p.top();
				match[p.top()] = i;
				p.pop();
			} else if (expression[i] == ',') {
                match[i] = - p.size();
            }

		}
        return helper(expression, 0, n - 1, match, 0);
    }
private:
	bool helper(string& e, int start, int end, vector<int>&match, int depth) {
		if (start == end) {
			if (e[start] == 'f') {
				return false;
			} else {
				return true;
			}
		}
        if (e[start] == '(' && match[start] == end) {
            return helper(e, start + 1, end - 1, match, depth + 1);
        }
        if (e[start] == '!') {
            return !helper(e, start + 2, end - 1, match, depth + 1);
        }
		if (e[start] == '&') {
			// & ( ... )	
			int pre = start + 2;
			for (int i = start + 1; i < end; ++i) {
                if (depth + 1 + match[i] == 0 || i == end - 1) {
                    auto r = helper(e, pre, i - (e[i] == ',' ? 1 : 0), match, depth + 1);
					if (r == false) {
						return false;
					}
					pre = i + 1;
				}
			}
			return true;
		} 
		if (e[start] == '|') {
            // | ( ... )
			int pre = start + 2;
			for (int i = start + 1; i < end; ++i) {
                if (depth + 1 + match[i] == 0 || i == end - 1) {
                    auto r = helper(e, pre, i - (e[i] == ',' ? 1 : 0), match, depth + 1);
                    if (r == true) {
						return true;
					}
					pre = i + 1;
                }
            }
			return false;
		}
		return true;
    }
};

int main() {
	string expression = "!(f)"; // true
    expression = "|(f,t)"; // true;
    expression = "&(t,f)";          /// false;
    expression = "|(&(t,f,t),!(t))";// false;
	expression = "!(&(!(&(f)),&(t),|(f,f,t)))";

    Solution s;
	cout << s.parseBoolExpr(expression) << endl;

	return 0;
}
