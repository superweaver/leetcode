#include "common.h"
class Solution {
public:
    string baseNeg2(int N) {
		const int Base = 2;
		string result;
		while(N) {
			result.push_back(N % Base + '0');
			N /= Base;
		}
		size_t i = 0;
		while(i < result.size()) {
			if (result[i] != '0') {
				int d = result[i]-'0';
				int carry = (d - (d % Base))/Base;
				bool negative = i & 1;
				d %= Base;
				if (negative) {
					carry += d;
				}
				if (carry) {
					if (i + 1 < result.size()) {
						result[i+1] += carry;
					} else {
						result.push_back(carry + '0');
					}
				}
				result[i] = d + '0';
			}
			i++;
		}
		reverse(result.begin(), result.end());
		return result.empty() ? "0" : result;
    }
};


int main() {
	vector<int> input = {2 , 3, 4};
	input = {43246421};
	Solution s;
	for(auto a : input) {
		cout << a << " : " << s.baseNeg2(a) << endl;
	}
	return 0;
}
