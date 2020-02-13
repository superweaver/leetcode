#include "common.h"
// https://github.com/tiankonguse/leetcode-solutions/tree/master/problemset-new/010/01040-moving-stones-until-consecutive-ii
// https://zxi.mytechroad.com/blog/leetcode/leetcode-weekly-contest-135-1037-1038-1039-1040/
// http://www.noteanddata.com/leetcode-1040-Moving-Stones-Until-Consecutive-II-java-solution-note.html

// analysis
// (1) to find the max steps
// assume we have no restriction that end stone can't be end stone
// then the max steps = the number of unoccupied holes
// then we have restriction
// case 1) no single end point in the initial stones, then equivalently we have no restriction
// case 2) only one single end point(A), on the other side, it is not a single point end(B)
//		   at this moment, move farthest point at B, move it to inner side of A. After it, case will be 1) or 2)
//		   in this case, the max steps is still equal to max steps without restriction
// case 3) there are two single end point, A and B
//		   we have to makde choice here
//		   move A to inner side of B
//		   or move B to inner side of A
//		   ater this first step, it will be converted to case 1
// (2) to find the min steps
//	   at last, n stones are grouped together
//	   equivalently, find a window of width <= n, count how many holes in this window, get the one with min holes
//	   corner case, if there is a window covering n-1 stones and the last stone's distance is > 1
//	   for example, 4, 5, 6, 10, we need two steps
class Solution
{
  public:
	vector<int> numMovesStonesII(vector<int> &stones)
	{
		int n = static_cast<int>(stones.size());
		sort(stones.begin(), stones.end());
		int max_step = stones.back() - stones.front() + 1 - n; // how many holes are there?
		int holes1 = stones[1] - stones[0] - 1;
		int holes2 = stones[n - 1] - stones[n - 2] - 1;
		// if (holes1 && holes2) { max_step -= min(holes1, holes2); }
		// this if() test can be omitted because in any of holes1 or holes2 is zero // the min of them is zero
		max_step -= min(holes1, holes2);

		int min_step = INT_MAX;
		int left = 0;							  // slow pointer
		for (int right = 0; right < n; ++right) { // fast pointer
			while (stones[right] - stones[left] + 1 > n) {
				left++;
			}
			// window width <= n
			int width = right - left + 1;
			if (width == n - 1 && stones[right] - stones[left] + 1 == n - 1) {
				// corner case
				min_step = min(min_step, 2); // it may first get 2, and then get zero later if all are consective
			} else {
				min_step = min(min_step, n - width);
			}
		}
		return {min_step, max_step};
	}
};
int main()
{
	vector<int> stones = {7, 4, 9};
	stones = {6,5,4,3,10};
	Solution s;
	displayvector(s.numMovesStonesII(stones));
	return 0;
}
