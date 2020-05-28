#include "common.h"

class Solution {
//https://www.cnblogs.com/grandyang/p/8367505.html
public:
	int findKthNumber(int m, int n, int k) {
	// same as find kth element in sorted matrix
		int low = 1;
		int high = m * n;
		while (low < high) {
			int mid = low + (high - low) / 2;
			int count = count_of_num_less_equal(m, n, mid);
			if (count < k) {
				low = mid + 1;
			}
			else {
				high = mid;
			}
		}
		return high;
	}
private:
	int count_of_num_less_equal1(int m, int n, int mid) {
		int count = 0;
		for (int i = 0; i < m; ++i) {
			if (mid > i * n) {
				count += n;			// there are i, 2*i, ... n*i are alll less than mid;
			}
			else {
				count += (mid / i); // at ith row, i, 2*i, ..., upto (mid/i)*i are all less than mid
			}
		}
		return count;

	}

	int count_of_num_less_equal2(int m, int n, int mid) {
		int i = m; // row
		int j = 1; // column
		int count = 0;
		while (i >= 1 && j <= n) {
			if (i * j <= mid) {
				// this column can be added
				count += i;
				j++;
			}
			else {
				--i;
			}
		}
		return count;
	}

	int count_of_num_less_equal(int m, int n, int mid) {
		int i = m; // row
		int j = 1; // column
		int count = 0;
		while (i >= 1 && j <= n) {
			//int next_j = (mid > i*n) ? (n + 1) : (mid / i + 1);
			int next_j = min(n, mid / i) + 1;
			count += (next_j - j) * i; // i is the height;
			i = mid / next_j;		// nextj, 2*next_j ,...,(mid/next_j)*next_j are <= mid
			j = next_j;
		}
		return count;
	}

};

int main() {

	Solution s;

	return 0;
}
