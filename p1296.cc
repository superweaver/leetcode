#include "common.h"
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k)
    {
        // good solution!!!
        if (nums.size() % k != 0) {
            return false;
        }
        vector<int> freq(k, 0); // so good
        for (int n : nums) {
            freq[n % k]++;
        }
        for (int i = 0; i < k - 1; i++) {
            if (freq[i] != freq[i + 1]) {
                return false;
            }
        }
        return true;
    }

    bool isPossibleDivide_my(vector<int>& nums, int K)
    {
        if (K == 1) {
            return true;
        }
        sort(nums.begin(), nums.end());
        vector<vector<int>> cache;
        size_t n = nums.size();
		size_t index = 0;

        for (size_t j = 0; j < n;) {
            size_t k = j;
            for (; k < n; ++k) {
                if (nums[k] > nums[j]) {
                    break;
                }
            }
            size_t len = k - j;
            if (cache.empty()) {
                for (size_t m = 0; m < len; ++m) {
                    cache.push_back({ nums[j] });
                }
				j = k;
                continue;
            }
            if (cache.size() - index > len) {
                return false;
            }
            for (size_t i = index; i < cache.size(); ++i) {
                if (nums[j] != cache[i].back() + 1) {
                    return false;
                } else {
                    cache[i].push_back(nums[j]);
                }
                if ((int)cache[i].size() == K) {
                    index++;
                }
                len--;
            }
            for (; len > 0; --len) {
                cache.push_back({ nums[j] });
            }
            j = k;
        }
        return index == cache.size();
    }
};
int main() {

    vector<int> nums = { 1, 2, 3, 3, 3, 4, 4, 4, 5, 5, 6, 6 };
    int k = 4;
	Solution s;
	cout << s.isPossibleDivide(nums, k) << endl; 
    return 0;
}
