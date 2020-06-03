#include "common.h"

class Solution {
public:
	string pushDominoes(string dominoes) {
		pair<char, int> pre('L', -1);
		dominoes.push_back('R');
		int i = 0;
		int n = dominoes.size();
		while (i < n) {
			while (i < n && dominoes[i] == '.') {
				i++;
			}
			if (i < n) {
				if (pre.first == 'L' && dominoes[i] == 'L') {
					for (int j = pre.second + 1; j < i; j++) {
						dominoes[j] = 'L';
					}
	 			}
				//if (pre.first == 'L' && dominoes[i] == 'R') {
					// do nothing
				//}
				if (pre.first == 'R' && dominoes[i] == 'L') {
					for (int j = pre.second + 1, k = i - 1; j < k; ++j, --k) {
						dominoes[j] = 'R';
						dominoes[k] = 'L';
					}
				}
				if (pre.first == 'R' && dominoes[i] == 'R') {
					for (int j = pre.second + 1; j < i; j++) {
						dominoes[j] = 'R';
					}
				}
				pre.first = dominoes[i];
				pre.second = i;
				++i;
			}
		}
		dominoes.pop_back();
		return dominoes;
	}
};

int main() {

	Solution s;

	return 0;
}
