#include "common.h"
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
		int n = arr.size();
		if (n < k) {
			return 0;
		}
        if (!threshold) {
            return n;
		}
        int t = threshold * k;
		int sum = 0;
		for (int i = 0; i < k; ++i) {
			sum += arr[i];
		}
		int result = sum >= t;
		for (int left = 0, right = k; right < n; left++, right++) {
			sum -= arr[left];
			sum += arr[right];
			result += (sum >= t);
		}
		return result;
    }
};

int main() {
    vector<int> arr = { 2, 2, 2, 2, 5, 5, 5, 8 };
    int k = 3, threshold = 4; // 3
	arr = {11,13,17,23,29,31,7,5,2,3}, k = 3, threshold = 5;// 6
	//arr = {7,7,7,7,7,7,7}, k = 7, threshold = 7;

    Solution s;
	cout << s.numOfSubarrays(arr, k , threshold) << endl;
    return 0;
}
