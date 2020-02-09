#include "common.h"
class Solution {
public:
    bool queryString(string S, int N) {
	//	const int Upper = 1e9;
		//bitset<Upper> flag;
		//bitset<1000000001> flag;
		int n = S.size();
		if (32 * n < N) {
			return false;
		}
		bitset<32001> flag;
		long current = 0;
		for (size_t i = 0; i < S.size(); ++i) {
			current = 0;
			for (size_t j = i; j < S.size(); ++j) {
				long temp = (current << 1) + S[j] - '0';
				if ( temp <= N) {
					current = temp;
					flag[current] = true;
				} else {
					break;
				}
			}
		}
		for (int i = 1 ; i <= N; ++i) {
			if (!flag[i]) {
				return false;
			}
		}
		return true;
    }

};
int main() {

	string S = "0110";
	int N = 3;
	S = "0110";
	N = 4;
	Solution s;
	cout << s.queryString(S, N) << endl;

	return 0;
}
