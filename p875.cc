#include "common.h"
class Solution {
public:
	int minEatingSpeed(vector<int>& piles, int H) {
		// binary search
		int low = 1;
		int high = 0;
		int n = piles.size();
		for (auto i : piles) {
			high = max(high, i);
		}
		while (low < high) {
			int mid = low + (high - low) / 2;
			bool r = check(mid, piles, H);
			if (r) {
				high = mid;
			}
			else {
				low = mid + 1;
			}
		}
		return low;
	}
private:
	bool check(int mid, vector<int>&piles, int H) {
		int count = 0;
		for (auto p : piles) {
			//count += (p / mid + ((p%mid == 0) ? 0 : 1));
            count += (p + mid - 1) / mid;
			if (count > H) {
				return false;
			}
		}
		return true;
	}
};

int main() {

	Solution s;

	return 0;
}
