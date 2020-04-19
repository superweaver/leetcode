#include "common.h"
class Solution {
public:
    int findMinFibonacciNumbers(int k) {
        // greedy
        vector<unsigned int> f;
        f.push_back(1);
        f.push_back(1);
        while(f.back() < k) {
			f.push_back(f.back() + f[f.size() - 2]);
		}
        int step = 0;
		for(int i = f.size() - 1; i >= 0; --i)
		{
            if (f[i] <= k) {
                k -= f[i];
                step++;
            }
		}
        return step;
	}
};

int main() {

    int k = 7; // 2
    k = 10; // 2
    k = 19; // 3
    k = 2353425;
	Solution s;
    cout << s.findMinFibonacciNumbers(k) << endl;

	return 0;
}
