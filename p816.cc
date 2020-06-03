#include "common.h"

class Solution {
public:
	vector<string> ambiguousCoordinates(string S) {
		return helper(S.substr(1, S.size() - 2));
	}
private:
	vector<string> helper(string s) {
		int n = s.size();
		vector<string> result;
		for(int i = 0; i < n-1; ++i)
		{
			vector<string> left = parse(s.substr(0, i + 1));
			if (left.empty()) {
				continue;
			}
			vector<string> right = parse(s.substr(i + 1));
			if (right.empty()) {
				continue;
			}
			for (auto&l : left) {
				for (auto&r : right) {
					result.push_back("(" + l + ", " + r + ")");
				}
			}
		}
		return result;
	}
	vector<string> parse(string s) {
		if (s.empty())return {};
		int n = s.size();
		if (s[0] == '0') {
			if (s.size() >1) {
				bool allzero = true;
				for (int i = 1; i < n; ++i) {
					if (s[i] != '0') {
						allzero = false;
						break;
					}
				}
				if (allzero) {
					return {};
				}
				else {
					if (s.back() == '0') {
						return {};
					}
					else {
						return { "0." + s.substr(1) };
					}
				}

			}
			else {
				return { "0" };
			}
		}
		else {
			vector<string> r;
			r.push_back(s);
			//if s.back() == 0, then there is only one parsing way
			if (s.back() != '0') {
				for (int i = 0; i < n - 1; ++i) {
					r.push_back(s.substr(0, i + 1) + "." + s.substr(i + 1));
				}
			}
			return r;
		}
	}
};

int main() {

	Solution s;

	return 0;
}
