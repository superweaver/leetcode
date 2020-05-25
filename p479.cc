#include "common.h"
class Solution {
public:
	// n <= 8
	// https://medium.com/@d_dchris/largest-palindrome-product-problem-brilliant-approach-using-mathematics-python2-leetcode-479-b3f2dd91b1aa
	// https://leetcode.com/problems/largest-palindrome-product/discuss/333879/16ms-code-c%2B%2B-with-math-explanation
	// for n > 0, the largest palindrom form by the product of two n digits number must be 2*n digits
	// p = first * second = (9^n - x) * (10^n - y)
	// p = 9^n * (10^n - (x+y)) + x*y
	// the string form of p is (ABC...) (...CBA)
	// p = 9^n * left + right
	// the string form of left and string form of right are palindrom
	// to make p as large as possible, we need left as large as possible
	// or make x+y as small as possible
	// define z = x + y
	// then we have left = 9^n - z;
	// then right = stol(reverse(itos(left))) = x*y > -1
	// equation right = x * y = (z-x)*x, z and right are know
	// we need to check if x^2 - z*x + right = 0 have integer solution
	// delta = b^2 - 4*ac = z^2 - 4*right must >= 0 && it must be square number
	// loop z , x and y are integer, then z >= 2
	int largestPalindrome(int n) {
		if (n == 1) return 9; // 1 * 9
		long long U = (long long)(pow(10, n));
		long long upper = (U - 1);
		for (long long z = 2; z <= upper; ++z) {
			if (n % 2 == 0) {
				// it must be this for n % 2 == 0
                // a short cut
				z = (long long)(pow(10, n / 2));
			}
			long long left = U - z;
			string str= to_string(left); // string for left
			reverse(str.begin(), str.end()); // string for right
			stringstream ss(str);
			long long right; 
			ss >> right;
			long long delta = z * z - 4 * right;
			if (delta < 0) continue;
			long long x1 = (long long)((z + sqrt(delta)) / 2);
			long long x2 = (long long)((z - sqrt(delta)) / 2);
			long long checkx1 = x1 * x1 - z * x1 + right;
			long long checkx2 = x2 * x2 - z * x2 + right;
			if (checkx1 == 0L || checkx2 == 0L) {
				//cout << "z = " << z << endl;
				//cout << "x1 = " << x1 << endl;
				return ((long long)(pow(10, n)) * left + right) % 1337L;
			}
		}
        return -1;
	}
};
//https://www.cnblogs.com/grandyang/p/7644725.html
class Solution2 {
public:
    int largestPalindrome(int n) {
        // 当n>1时，两个n位数乘积的最大回文数一定是2n位的。
        int upper = pow(10, n) - 1, lower = upper / 10;
        for (int i = upper; i > lower; --i) {
            string t = to_string(i);
            long p = stol(t + string(t.rbegin(), t.rend()));
            for (long j = upper; j * j > p; --j) {
                if (p % j == 0) return p % 1337;
            }
        }
        return 9;
    }
};

int main() {

	Solution s;

	return 0;
}
