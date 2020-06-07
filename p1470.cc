#include "common.h"
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> r(n*2,0);
        int m = n;
        for (int i = 0; i < m; ++i) {
            r[2*i] = nums[i];
            r[2*i+1] = nums[i+m];
        }
        //n *= 2; for (int i = m; i < n; ++i) { r[2 * (i-m) + 1] = nums[i]; }
        return r;
    }
};

int main() {
    vector<int> nums = {2,5,1,3,4,7};
    int n = 3;

    //nums ={1,2,3,4,4,3,2,1};
    //n = 4;
    //1 3 2 4 4 3 2 1


	Solution s;
    displayvector(s.shuffle(nums, n));

	return 0;
}
