#include "common.h"
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
		int n = arr.size();
		int rightMax = -1;
		int t = 0;
		int *p = &arr[n-1];
		while(n--) {
			t = *p;
			*(p--) = rightMax;
			if (t > rightMax) {
				rightMax = t;
			}
		}
		return arr;
    }
};

int main() {
    vector<int> arr = { 17, 18, 5, 4, 6, 1 };
    Solution s;
	displayvector(s.replaceElements(arr));
    return 0;
}
