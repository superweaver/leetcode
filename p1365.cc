#include "common.h"
class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
		vector<pair<int, int>> cache;
		int n = nums.size();
		for(int i = 0; i < n; ++i) {
			cache.push_back({nums[i], i});
		}
		sort(cache.begin(), cache.end());
		vector<int> result(n, 0);
		for (int i = 0; i < n;) {
			int j = i;
			while (j < n && cache[j].first == cache[i].first) {
				result[cache[j].second] = i; // i is also the number of smaller elements
				j++;
			}
			i = j;
		}
		return result;
    }
};

int main() {
	vector<int> nums = {8,1,2,2,3};
	nums = {6, 5, 4, 8};
	nums = {7, 7, 7, 7};
	Solution s;
	displayvector(s.smallerNumbersThanCurrent(nums));
	return 0;
}
