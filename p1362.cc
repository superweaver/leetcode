#include "common.h"
class Solution {
public:
    vector<int> closestDivisors(int num) {
        vector<int> candidates{num + 1, num + 2};
        int c = sqrt(candidates.back()) ;
        for (; c >= 1; --c) {
            for (auto candidate : candidates) {
                if (candidate % c == 0) {
                    return {c, candidate / c};
                    //safe to return result;
                    //later distance is larger
                }
            }
        }
        return {};
    }
};

int main() {
     vector<int> input = {8, 123, 999};
	Solution s;
    for(auto i:input) {
        displayvector(s.closestDivisors(i));
    }

	return 0;
}
