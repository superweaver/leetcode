#include "common.h"
class Solution {
public:
    // 111
    // 101
    // =
    // 10010
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2)
    {
        reverse(arr1.begin(), arr1.end());
        reverse(arr2.begin(), arr2.end());
        vector<int> result;
        int carry = 0;
        size_t index = 0;  // postive == !(index&1);
        while (true) {
            int v1 = index < arr1.size() ? arr1[index] : 0;
            int v2 = index < arr2.size() ? arr2[index] : 0;
            int v = v1 + v2;
            if (index & 1) {
                v = -v;
            }
            v += carry;                  // real value here
            int remainder = abs(v) % 2;  // !!!
            carry = (v - ((index & 1) ? -remainder : remainder)) / 2;
            result.push_back(remainder);
            ++index;
            if (index >= arr1.size() && index >= arr2.size() && (carry == 0)) {
                break;
            }
        }
		while(result.size() > 1 && result.back() == 0) {
			result.pop_back();
		}
        reverse(result.begin(), result.end());
        return result;
    }
};

int main()
{

    vector<int> arr1 = { 1, 1, 1, 1, 1 }, arr2 = { 1, 0, 1 };  // 10000
    arr1 = { 1, 1, 1 }, arr2 = { 1, 0, 1 };                    //
    arr1 = { 1, 1, 1, 1, 0, 1 }, arr2 = { 1, 0, 1, 1, 0, 0, 1, 0, 1 }; // [1,0,0,0,1,0,1,1,0]
    Solution s;
    displayvector(s.addNegabinary(arr1, arr2));
    return 0;
}
