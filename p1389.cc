#include "common.h"
class Solution {
public:
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
		//  the insertion operations will be valid.
		int n = index.size();
        vector<int> result(n, 0);
        // not good
		for (int i = 0; i < n; ++i) {
            result.insert(result.begin() + index[i], nums[i]);
        }
        return result;
    }
};

int main() {
    vector<int> nums = { 0, 1, 2, 3, 4 }, index = { 0, 1, 2, 2, 1 };
    nums = { 1, 2, 3, 4, 0 }, index = { 0, 1, 2, 3, 0 };
    nums = { 4, 2, 4, 3, 2 }, index = { 0, 0, 1, 3, 1 };

    Solution s;
	printElements(s.createTargetArray(nums, index));

	return 0;
}
