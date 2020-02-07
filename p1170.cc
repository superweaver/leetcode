#include "common.h"
class Solution {
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
		vector<int> fw;
		for (auto &s : words) {
			fw.push_back(f(s));
		}
		sort(fw.begin(), fw.end());
		vector<int> result;
		for (auto& s : queries) {
			result.push_back(distance(upper_bound(fw.begin(), fw.end(), f(s)), fw.end()));
		}
		return result;
    }
private:
	int f(const string &s) {
		char low = 'z' + 1;
		int count = 1;
		for (auto c : s) {
			if (c == low) {
				count ++;
			} else if (c < low) {
				low = c;
				count = 1;
			}
		}
		return count;
	}
};

int main() {
	vector<string> queries = {"bbb","cc"}, words = {"a","aa","aaa","aaaa"};
	Solution s;
	displayvector(s.numSmallerByFrequency(queries, words));
	return 0;
}
