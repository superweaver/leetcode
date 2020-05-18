#include "common.h"
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> q;
        int n = nums.size();
        vector<int> result;
        for (int i = 0; i < n; ++i) {
            while(!q.empty() && nums[i] > nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(i);
            while(!q.empty() && i - q.front() >= k) {
                q.pop_front();
            }
            if (i >= k-1) {
                result.push_back(nums[q.front()]);
            }
        }
        return result;
    }
};

int main() {

    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;

	Solution s;
    displayvector(s.maxSlidingWindow(nums, k));

	return 0;
}
