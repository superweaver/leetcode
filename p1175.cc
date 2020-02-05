#include "common.h"
class Solution {
public:
    int numPrimeArrangements(int n) {
		vector<bool> p(n, true);
		p[0] = false;
		int count = 0;
		for (int i = 1; i < n; ++i) {
			if (p[i]) {
				int v = i + 1;
				count++;
				for (int j = i + v; j < n; j += v) {
					p[j] = false;
				}
			}
		}
		// count! * (n-count) !
		long result = 1;
		int a = n - count;
		const int Mod = 1000000007;
		while(a) {
			result = (result * a) % Mod;
			a--;
		}
		a = count;
		while(a) {
			result = (result * a) % Mod;
			a--;
		}
		return result;
    }
};

int main() {

	Solution s;
	cout << s.numPrimeArrangements(5) << endl;
	cout << s.numPrimeArrangements(100) << endl;
	return 0;
}
