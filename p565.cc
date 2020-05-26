#include "common.h"

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        vector<int> back(nums);
        int n = nums.size();
        int r = INT_MIN;
        for(int i = 0; i < n; ++i) {
            // starting at index i of nums, what is the length of such arry
            if (nums[i] < 0) continue; // visited
            int current = i;
            int next = nums[current];
            int len = 1;
            while (next != i) {
                current = next;
                next = nums[current];
                nums[current] = -1; // we can also use nums[current]+=n; to mark it as visited
                len++;
            }
            nums[i] = -1;
            r = max(r, len);
        }
        swap(nums, back);
        return r;
    }
};


int main() {

	Solution s;

	return 0;
}
