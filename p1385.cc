#include "common.h"
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
		sort(arr2.begin(), arr2.end());	
		vector<int> count(2001, 0); // i - 1000; act as counter
		for (auto a : arr1) {
			count[a + 1000]++;	
		}
        int counter = 0;  // [a1 -d, a2 + d]
        for (int i = 0; i < 2001; ++i) {
            if (count[i]) {
				int a1 = i - 1000;
				int a2_lower = i - 1000 - d;
				int a2_upper = i - 1000 + d;
                auto it_lower = lower_bound(arr2.rbegin(), arr2.rend(), a1, greater<int>());
                if (it_lower != arr2.rend() && *it_lower >= a2_lower) {
                    counter += count[i];
                    continue;
                }
                auto it_upper = lower_bound(arr2.begin(), arr2.end(), a1);
                if (it_upper != arr2.end() && *it_upper <= a2_upper) {
                    counter += count[i];
                    continue;
                }
            }
        }
        return arr1.size() - counter;
    }
};

int main() {
    vector<int> arr1 = { 4, 5, 8 }, arr2 = { 10, 9, 1, 8 };
    int d = 2; // 2
    //arr1 = { 1, 4, 2, 3 }, arr2 = { -4, -3, 6, 10, 20, 30 }, d = 3;  // 2
	arr1 = {2,1,100,3}, arr2 = {-5,-2,10,-3,7}, d = 6; // 1


    Solution s;
	cout << s.findTheDistanceValue(arr1, arr2, d) << endl;

    return 0;
}
