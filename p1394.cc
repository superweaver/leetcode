#include "common.h"
// 1 <= arr.length <= 500
// 1 <= arr[i] <= 500
class Solution {
public:
    int findLucky(vector<int>& arr) {
		constexpr size_t N = 501;
		vector<int> counter(N, 0);
		for (auto i : arr) {
			counter[i]++;
		}
		// !!! must exclude 0
		for (int i = counter.size() - 1; i > 0; --i) {
			// back to front, if any return the largest of them
			if (counter[i] == i) {
				return i;
			}
		}
		// not found
		return -1;
    }
};

int main() {

    vector<int> arr = { 2, 2, 3, 4 }; // 2
    arr = { 1, 2, 2, 3, 3, 3 };       // 3
	arr = {2,2,2,3,3};  // -1
    Solution s;
	cout << s.findLucky(arr) << endl;

	return 0;
}
