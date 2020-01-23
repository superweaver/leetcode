#include "common.h"
class Solution {
    public:
        int tribonacci(int n) {
            // T0 = 0, T1 = 1, T2 = 1;
            // Tn+3 = Tn+2 + Tn+1 + Tn
            // 0 <= n <= 37
            if (n < 2){
                return n;
            } else if (n < 3){
                return 1;
            }
            vector<int> cache(n+1, 0);
            cache[0] = 0;
            cache[1] = cache[2] = 1;
            int sum = cache[0] + cache[1] + cache[2];
            for (int i = 3; i <=n; ++i) {
                cache[i] = sum;
                sum -= cache[i-3];
                if (i < 37) {
                    sum += cache[i];
                }
            }
            return cache[n];
        }
};

int main() {
    int n = 37;
    Solution s;
    cout << s.tribonacci(n) << endl;
    return 0;
}
