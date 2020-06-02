#include "common.h"
class Solution {
public:
	int preimageSizeFZF(int K) {
		// 5 or zero
		// f(x) = K = x/5 + x/25 + ....
		// K <= x/5.0 + x/25.0 .... = x/4.0
		// x >= 4*k; // left boundary
		// https://www.cnblogs.com/grandyang/p/9214055.html
		// right boundary?
		// again assume f(x) = K
		// will x <= 5K?
		// if (x > 5k)
		// then f(x) >= f(5k) = 5k/5 + 5k/25 + .. >= k
		// set right boundary to be 5(k+1)
		// binary search [4*K, 5(K+1)]
		long long left = (long long)K * 4L;
		long long right = (long long)(K + 1) * 5L;
		while(left < right) {
			long long mid = left + (right - left) / 2;
			int k = getFactorialZeros(mid);
			if (k == K) return 5;
			if (k < K) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		return 0;
	}
private:
	long getFactorialZeros(long long x) {
		 long long c = 0;
		while (x) {
			x /= 5;
			c += x;
		}
		return c;
	}
};

class Solution {
public:
    //https://www.cnblogs.com/grandyang/p/9214055.html
    int preimageSizeFZF_observation(int K) {
        if (K < 5) return 5;
        int base = 1;
        while (base * 5 + 1 <= K) {
            base = base * 5 + 1;
        }
        if (K / base == 5) return 0;
        return preimageSizeFZF_observation(K % base);
    }
};

int main() {

	Solution s;

	return 0;
}
