#include "common.h"
class Solution {
  public:
    bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
        set<long> cache;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {

            if (cache.size() == k + 1) {
                // at most it can have k + 1 elements
                // nums[i - k - 1] should be excluded for comparison with nums[i]
                // remove
                auto head = nums[i - k - 1];
                cache.erase(head);
            }

            auto it = cache.lower_bound(long(nums[i]) - t);
            if (it == cache.end()) {
                cache.insert(nums[i]);
            } else {
                // fuck overflow
                if (*it - nums[i] <= t) { // use - to prevent overflow
                    return true;
                } else {
                    cache.insert(nums[i]);
                }
            }
        }
        return false;
    }
};

int main() {

    vector<int> nums = {1,2,3,1};
    int k = 3;
    int t = 0; // true
    nums = {1,0,1,1}, k = 1, t = 2; // true
    nums = {1,5,9,1,5,9}, k = 2, t = 3; // false
    nums = {0, 2147483647}; k = 1; t = 2147483647;// true

    //nums = {2147483647, -2147483647}; k = 1; t = 2147483647; // false;

    Solution s;
    cout << s.containsNearbyAlmostDuplicate(nums, k, t) << endl;

    return 0;
}
