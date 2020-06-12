#include "common.h"
class Solution {
public:
	vector<bool> camelMatch(vector<string>& queries, string pattern) {
		vector<bool> result;
		for (auto&q : queries) {
			result.push_back(helper(q, pattern));
		}
		return result;
	}
private:
	bool helper(string&query, string&pattern) {
		if (query.size() < pattern.size()) {
			return false;
		}
		size_t iq = 0;
		size_t ip = 0;
		while (iq < query.size()) {
			if (ip == pattern.size()) {
				while (iq < query.size()) {
					if (query[iq] >= 'A' && query[iq] <= 'Z') {
						return false;
					}
					iq++;
				}
				return iq == query.size();
			}
			else {
				char c = pattern[ip];
				if (c >= 'a' && c <= 'z') {
					while (iq < query.size()) {
						if (query[iq] >= 'A' && query[iq] <= 'Z') {
							return false;
						}
						else {
							if (query[iq] == c) {
								iq++;
								ip++;
								break;
							}
							else {
								iq++;
							}
						}
					}
				}
				else {
					while (iq < query.size()) {
						if (query[iq] >= 'A' && query[iq] <= 'Z') {
							if (query[iq] == c) {
								iq++;
								ip++;
								break;
							}
							else {
								return false;
							}
						}
						else {
							iq++;
						}
					}
				}
			}
		}
		return ip == pattern.size();
	}
};

int main() {

	Solution s;

	return 0;
}
