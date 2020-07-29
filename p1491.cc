#include "common.h"
class Solution {
public:
    double average(vector<int>& salary) {
        int m = INT_MAX;
        int M = INT_MIN;
        int total = 0;
        for (auto s : salary) {
            m = min(m, s);
            M = max(M, s);
            total += s;
        }
        return double(total - m - M) / (salary.size() - 2);
    }
};

int main() {

	Solution s;

	return 0;
}
