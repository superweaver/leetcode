#include "common.h"
class Solution {
public:
    string minRemoveToMakeValid(string s) {
		int n = s.size();
		vector<int> stk;
		for (int i = 0; i < n; ++i) {
			if (s[i] == '(') {
				stk.push_back(i);
			} else if (s[i] == ')') {
				if (stk.empty()) {
					stk.push_back(i);
				} else {
					if (s[stk.back()] == '(') {
						stk.pop_back();
					} else {
						stk.push_back(i);
					}
				}
			}
		}
		int pre = -1;
		stk.push_back(n);
		string result;
		for (auto i : stk) {
            result += s.substr(pre + 1, i - pre - 1);
			pre = i;
        }
		return result;
    }
};

int main() {

	string str = "lee(t(c)o)de)";
	str = "a)b(c)d";
	str = "))((";
	str = "(a(b(c)d)";
	Solution s;
	cout << s.minRemoveToMakeValid(str) << endl;

	return 0;
}
