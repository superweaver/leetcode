#include "common.h"
class Solution {
public:
    int kthFactor(int n, int k) {
        // Consider a list of all factors of n sorted in ascending order, return the kth factor in this list or return -1 if n has less than k factors.
        // 1 <= k <= n <= 1000
        int bound = sqrt(n);
        vector<int> factors;
        int i = 0;
        for (int i = 1;i <= bound; ++i) {
            if (n % i == 0) {
                factors.push_back(i);
                if ((n / i) != i) {
                    factors.push_back(n / i);
                }
                if (factors.size() >= (2 * k - 1)) {
                    return factors[2*(k-1)];
                }
            }
        }
        if (factors.size() < k) {
            return -1;
        }
        // actually no need to sort
        // can pick from it
        sort(factors.begin(), factors.end());
        return factors[k - 1];
    }
};

int main() {
    int n = 1000, k = 3; // 4
    n = 1, k = 1;
    n = 4, k = 4;
    n = 7, k = 2;
    n = 12, k = 3;
	Solution s;
    cout << s.kthFactor(n, k) << endl;

	return 0;
}
