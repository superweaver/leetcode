#include "common.h"
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        if (m <= 0 || n <= 0) return 0;
        if (ops.empty() || ops[0].empty()) return m * n;// fuck it
        int a = INT_MAX;
        int b = INT_MAX;
        for (auto& v : ops){
            a = min(a, v[0]);
            b = min(b, v[1]);
        }
        // for element in range row [0..a) and column [0..b)
        // they are increased by one in every operation
        // so they are the max
        return a * b;
    }
};

int main() {

	Solution s;

	return 0;
}
