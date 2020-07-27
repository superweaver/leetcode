#include "common.h"
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        constexpr int Mod = 1e9 + 7;
        // record the number of subarray endign at index i whose sum is odd
        int n = arr.size();
        // vector<int> count_odd(n, 0);
        // vector<int> count_even(n, 0);
        // for index i, count_odd[i] + count_even[i] = i + 1
        // if (arr[i]&1) { 
        //     count_odd[i] += count_even[i-1] + 1;
        // } else {
        //     count_odd[i] += count_odd[i-1]
        // }
        int result = 0;
        // base case
        int count_odd = arr[0] & 1;
        result += count_odd;

        for (int i = 1; i < n; ++i) {
            if (arr[i]&1) {
                // current is odd
                // count_odd[i] = ((i-1) + 1) - count_odd[i-1] + 1
                count_odd = (i - count_odd) + 1;
            } else {
                //count_odd[i] = count_odd[i-1];
            }
            result = (result + count_odd) % Mod;
        }
        return result;
    }
};

int main() {
    vector<int> arr = {1, 3, 5};
    arr = {1, 2, 3, 4, 5, 6, 7};

    Solution s;
    cout << s.numOfSubarrays(arr) << endl;

	return 0;
}
