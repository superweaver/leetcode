#include "common.h"
class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
		int maxvalue = -1;
        int total = 0;
		int n = arr.size();	
		for (auto i : arr) {
			maxvalue = max(maxvalue, i);
			total += i;
		}
		if (total <= target) {
			return maxvalue;
		}
        sort(arr.begin(), arr.end());
		vector<int> prefix_sum(n+1, 0);
		for (int i = 0; i < n; ++i) {
			prefix_sum[i + 1] = prefix_sum[i] + arr[i];
		}
		int result = INT_MAX;
		int diff = INT_MAX;
		// find first i that makes sum[arr[0, i)] + (n - i)* arr[i] >= 0
		int low = 0;
		int high = arr[n-1];
        while (low  < high) {
            int mid = low + (high - low) / 2;
			auto it = lower_bound(arr.begin(), arr.end(), mid);
			int index = distance(arr.begin(), it);
			int d = prefix_sum[index] + mid * (n - index) - target;
			if (d == 0) {
				return mid;
			} else if (d < 0) {
				low = mid + 1;
				if (abs(d) < diff) {
					diff = abs(d);
					result = mid;
				} else if (abs(d) == diff) {
					result = min(result, mid);
				}
			} else {
				high = mid;
                if (abs(d) < diff) {
                    diff = abs(d);
                    result = mid;
                } else if (abs(d) == diff) {
                    result = min(result, mid);
                }
          }
        }
        return result;
    }
};

int main() {

    vector<int> arr = { 4, 9, 3 }; // 3
	int target = 10;
	arr = {2,3,5}, target = 10 ; // 5
    arr = { 60864, 25176, 27249, 21296, 20204 }, target = 56803;  // 11361
    Solution s;
	cout << s.findBestValue(arr, target) << endl;

	return 0;
}
