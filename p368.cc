#include "common.h"
//https://leetcode.com/problems/largest-divisible-subset/discuss/83998/C%2B%2B-Solution-with-Explanations
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<int> T(nums.size(), 0);      // length
        vector<int> parent(nums.size(), 0); // track parent

        int m = 0; // max len
        int mi = 0; // corresponding start index

        // iterate from end to start since it's easier to track the answer index
        for(int i = nums.size() - 1; i >= 0; --i)
        {
            for(int j = i; j < nums.size(); ++j)
            {
                // if(nums[i] % nums[j] == 0 && T[i] < 1 + T[j]) // if extending by larger elements
                // check every a[j] that is larger than a[i]
                if(nums[j] % nums[i] == 0 && T[i] < 1 + T[j])
                {
                    // if a[j] mod a[i] == 0, it means T[j] can form a larger subset by putting a[i] into T[j]
                    T[i] = 1 + T[j];
                    parent[i] = j; // j->i, j < i
                    if (T[i] > m) {
                        m = T[i];
                        mi = i;
                    }
                }
            }
        }

        vector<int> ret;
        for (int i = 0; i < m; ++i) {
            ret.push_back(nums[mi]);
            mi = parent[mi];
        }
        return ret;
    }
};

int main() {

	Solution s;

	return 0;
}
