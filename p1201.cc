#include "common.h"
class Solution {
    typedef long long LL;

public:
    int nthUglyNumber(int n, int a, int b, int c)
    {
        // A U B U C = A + B + C - A and B - B and C - A and C + A and B and C
        int low = 1;
        int high = (int)2e10;
        vector<int> cache{ a, b, c };
        sort(cache.begin(), cache.end());
        a = cache[0];
        b = cache[1];
        c = cache[2];
        // binary search
        int candidate = binarySearch(low, high, a, b, c, n);
        int result = 0;
        for (auto i : cache) {
            result = max(result, candidate / i * i);
        }
        return result;
    }

private:
    int binarySearch(LL low, LL high, LL a, LL b, LL c, LL n)
    {
        LL gcd_ab = gcd(a, b);
        LL ab = a * b / gcd_ab;
        LL gcd_ac = gcd(a, c);
        LL ac = a * c / gcd_ac;
        LL gcd_bc = gcd(b, c);
        LL bc = b * c / gcd_bc;
        LL gcd_abc = gcd(ab, c);
        LL abc = ab * c / gcd_abc;
        while (low + 1 < high) {
            LL mid = low + (high - low) / 2;
            LL count = mid / a + mid / b + mid / c - mid / ab - mid / ac - mid / bc + mid / abc;
            if (count == n) {
                return mid;
            } else if (count < n) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }
    
    LL gcd(LL a, LL b)
    {
        if (a == b) {
            return a;
        }
        if (a < b) {
            swap(a, b);
        }
        while (b) {
            LL c = a % b;
            a = b;
            b = c;
        }
        return a;
    }
};

int main()
{
    int n = 1000000000, a = 2, b = 217983653, c = 336916467;  // 1999999984
    n = 5, a = 2, b = 11, c = 13;                             // 10
    n = 4, a = 2, b = 3, c = 4;                               // 6
    n = 3, a = 2, b = 3, c = 5;                               // 4
    n = 5, a = 2, b = 3, c = 3;
    Solution s;
    cout << s.nthUglyNumber(n, a, b, c) << endl;
    return 0;
}
