#include "common.h"
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
		vector<int> count(2001, 0);
		for (auto i : arr) {
			count[i + 1000]++;
		}
		unordered_set<int> f;		
		for (auto c: count) {
			if (c) {
				if (f.count(c)) {
					return false;
				} else {
					f.insert(c);
				}
			}
		}
		return true;
    }
};

int main() {

	vector<int> arr = {-3,0,1,-3,1,1,1,-3,10,0};
	arr = {1, 2};
	Solution s;
	cout << s.uniqueOccurrences(arr) << endl;
	return 0;
}
