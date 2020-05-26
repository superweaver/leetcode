#include "common.h"

class Solution {
//https://blog.csdn.net/TstsUgeg/article/details/62427718
//http://startleetcode.blogspot.com/2017/02/517-super-washing-machines.html
public:
	int findMinMoves(vector<int>& machines) {
		int n = machines.size();
		if (n == 0) return 0;
		vector<int> sum(n + 1, 0);
		// sum[i] mean sum of machines [0...i) , i = 0..n-1
		for (int i = 1; i < n + 1; ++i) {
			sum[i] = sum[i - 1] + machines[i-1];
		}
		// the total sum is sum[n]
		if (sum.back() % n != 0) {
			return -1;
		}
		int ave = sum.back() / n;
		int result = INT_MIN;
		for (int i = 0; i < n; ++i) {
			int left = sum[i] - ave * i; // if left < 0, then need to pass <left> amount from node i to left
			// if left > 0, left side will pass <left> amount to left
			int right = sum.back() - sum[i + 1] - ave * (n - i - 1);
			int mv = 0;
			if (left > 0 && right > 0) {
				// left side and right side can pass to node i at the same time
				mv = max(left, right);
			}
			else if (left < 0 && right < 0) {
				// left side and right side can not pass to node i at the same time
				mv = -left - right;
			}
			else {
				// one side can transfer to node i, and node i can transfer to other side
				mv = max(abs(left), abs(right));
			}
			result = max(mv, result);
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
