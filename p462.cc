#include "common.h"
class Solution {
    //https://www.cnblogs.com/grandyang/p/6089060.html
public:
    // equivalent to find the median of the array
    // this is the defintion of median // min(abs(x-a_i))
    //
    // can use quick selection to get it
    // then no need to sort it
    int minMoves2(vector<int>& nums) {
        int res = 0, n = nums.size(), mid = n / 2;
        nth_element(nums.begin(), nums.begin() + mid, nums.end());
        for (int i = 0; i < n; ++i) {
            res += abs(nums[i] - nums[mid]);
        }
        return res;
    }
};

class Solution_my {
public:
	int minMoves2(vector<int>& nums) {
		// s = min(sum(|x_bar - x_i|))
		if (nums.empty()) return 0;
		sort(nums.begin(), nums.end());
		vector<long> summation(nums.size(), 0L);
		summation[0] = nums[0];
		for (size_t i = 1; i < summation.size(); ++i) {
			summation[i] = nums[i] + summation[i - 1];
		}
		int n = nums.size();
		int low = nums[0];
		int high = nums[n - 1];
		while (low < high) {
			if (low + 2 <= high) {
				int mid = low + (high - low) / 2;
				long s = getcost(mid, nums, summation);
				long s_left = getcost(mid - 1, nums, summation);
				long s_right = getcost(mid + 1, nums, summation);
				if (s < s_left && s < s_right) {
					return s;
				}
				else if (s < s_left && s_right < s) {
					low = mid + 1;
				}
				else if (s < s_right&&s_left < s) {
					high = mid - 1;
				}
				else if (s < s_left && s == s_right) {
					low = mid;
				}
				else if (s_right > s && s == s_left) {
					high = mid;
				}
				else {
					return s;
				}
			}
			else {
				return min(getcost(low, nums, summation), getcost(high, nums, summation));
			}
		}
		return  getcost(low, nums, summation);
	}
private:
	unordered_map<int, long> cache; // x_bar : sum(|x_bar - x_i|);
	long getcost(int target, const vector<int>& nums, const vector<long>& summation) {
		if (cache.find(target) != cache.end()) {
			return cache[target];
		}
		auto it = upper_bound(nums.begin(), nums.end(), target); // > target
		auto it2 = lower_bound(nums.begin(), nums.end(), target); // >= target
		int larger = distance(it, nums.end());
		int equal = distance(it2, it);
		int less = nums.size() - larger - equal;
		long cost = 0L;
		long total = summation.back();
		long sum_less = 0L;
		if (less > 0) {
			sum_less = summation[less - 1];
		}
		cost += less * target - sum_less;
		cost += total - sum_less - (larger + equal) * target;
		cache[target] = cost;
		return cost;
	}
};

int main() {

	Solution s;

	return 0;
}
