#include "common.h"
class Solution {
public:
	int maxChunksToSorted(vector<int>& arr) {
		vector<pair<int, int>> parr; // value and its initial index
		int n = arr.size();
		for (int i = 0; i < n; ++i) {
			parr.push_back({ arr[i],i });
		}
		sort(parr.begin(), parr.end()); 
		int r = 0; // final result
		int sum = 0; // index summation
		int desired = 0;
		for (int i = 0; i < n; ++i) {
			desired += i;
			sum += parr[i].second;
			if (sum == desired) { // !!! nice
				r++;
			}
		}
		return r;
	}
};

int main() {

	Solution s;

	return 0;
}
