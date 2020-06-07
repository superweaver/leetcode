#include "common.h"
class Solution {
public:
	//https://www.cnblogs.com/grandyang/p/11361245.html
    /*
     * 如果不考虑数字修改，那么原数组的最大值最小值之间的差值就是所求，这里可以当作结果 res 的初始值。由于每个数字都需要加K或者减K，为了使得新数组的最大值最小值的差值最小，应该尽量使原数组中的较小的数字加K，较大的数字减K，所以最好是先给原数组排个序，然后在数组的某个位置i为界限，将原数组分为两段，前面所有的数字都加K，后面所有的数字都减K。则前半段 [0, i] 中的最大值是 A[i]+K，最小值是 A[0]+K，后半段 [i+1, n-1] 范围内的最大值是 A[n-1]-K，最小值是 A[i+1]-K，所以整个数组的最大值是 A[i]+K 和 A[n-1]-K 中的较大值，最小值是 A[0]+K 和 A[i+1]-K 中的较小值，二者做差就是可能的结果了，遍历所有的i，用每次计算出的差值来更新结果 res 即可
     * */
	int smallestRangeII(vector<int>& A, int K) {
		sort(A.begin(), A.end());
		int n = A.size();
		int r = A[n - 1] - A[0];
		int left_min = A[0] + K;
		int right_max = A[n - 1] - K;
		for (int i = 0; i < n - 1; ++i) {
			// i is the last index of left part
			int low = min(left_min, A[i + 1] - K);
			int high = max(right_max, A[i] + K);
			r = min(high - low, r);
		}
		return r;
	}
};

int main() {

	Solution s;

	return 0;
}
