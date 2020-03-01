#include "common.h"
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
		int result = 0;	
		unordered_map<int, int> count;
		for (auto i : arr) {
			if (count.count(i - difference)) {
				count[i] = count[i - difference] + 1;
			} else {
				count[i] = 1;
			}
			result = max(result, count[i]);
		}
		return result;
    }
};

int main() {

    vector<int> arr = { 1, 5, 7, 8, 5, 3, 4, 2, 1 };
    int difference = -2;
    Solution s;
	cout << s.longestSubsequence(arr, difference) << endl;

	return 0;
}
