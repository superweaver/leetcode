#include "common.h"
class Solution {
public:
    vector<int> decompressRLElist(vector<int>& nums) {
        vector<int> result;
        int n = nums.size();
        for (int i = 0; i < n ; i += 2) {
            result.insert(result.end(), nums[i], nums[i+1]);
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
