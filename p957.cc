#include "common.h"
class Solution {
public:
	vector<int> prisonAfterNDays(vector<int>& cells, int N) {
		unsigned char state = 0;
		for (auto i : cells) {
			state <<= 1;
			state += i;
		}
		unsigned char mask = 0x7e; // 0x0111 1110
		int period = 0;
		state = ((~((state << 1) ^ (state >> 1)))) & mask;
		unsigned char init_state = state;
		int n = N - 1;
		//unordered_set<unsigned char> visited;
		while (n--) {
			state = ((~((state << 1) ^ (state >> 1)))) & mask;
			if (state == init_state) {
				period = N - 1 - n;
				break;
			}
		}
		if (period) {
			n %= period;
			while (n--) {
				state = ((~((state << 1) ^ (state >> 1)))) & mask;
			}
		}
		vector<int> result(8);
		for (int i = 7; i >= 0; --i) {
			result[i] = state & 1;
			state >>= 1;
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
