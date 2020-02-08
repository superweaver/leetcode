#include "common.h"
class Solution {
public:
    int numDupDigitsAtMostN(int N) {
		vector<int> digits;       
		int n = N;
		while(n) {
			digits.push_back(n % 10);
			n /= 10;
		}
		// count how many number of positive intergers with distinct digits that are <= N
		reverse(digits.begin(), digits.end());
		int count = 0;
		set<int> visited;
		// no heading zeros
		helper(count, 0, digits, visited);
		// heading zeros involves
		// note : 0 itself can't be counted 
		for (size_t len = 1; len < digits.size(); ++len) {
			count += 9 * Permuation(9, digits.size() - len - 1);
		}
		return N - count;
    }
private:
	void helper(int& count, size_t start, vector<int>&digits , set<int>& visited) {
		if(start >= digits.size()) {
			count++;
			return;
		}
		int current = digits[start];
		// less
		int p = Permuation(10 - visited.size() - 1, digits.size() - 1 - start);
		for (int i = (start == 0) ? 1 : 0; i < current; ++i) {
			if (visited.count(i)) {
				continue;
			}
			count += p;
		}
		// equal
		if (visited.count(current)) {
			return;
		} else {
			visited.insert(current);
			helper(count, start + 1, digits, visited);
		}
	}
	int Permuation(int n, int k){
		if (n < k) return 0;
		if (k == 0) {
			return 1;
		}
		int r = 1;
		while(k--){
			r *= n--;
		}
		return r;
	}
};
int main() {
	vector<int> input = {1, 9, 10, 20, 100, 1000};
//	input = {2432789};
//	input = {789};
	Solution s;
	for (auto i : input) {
		cout << i << " : " << s.numDupDigitsAtMostN(i) << endl;
	}
	return 0;
}
