#include "common.h"
class Solution1 {
public:
    vector<int> countBits(int num) {
        vector<int> ret(num + 1, 0);
        // i is not 0
        for (int i = 1; i <= num; ++i) {
            // nice
            ret[i] = ret[i & (i - 1)] + 1;
        }
        return ret;
    }
};
class Solution {
    public:
        vector<int> countBits(int num) {
            // num non negative
            int size = num + 1;
            vector<int> result(size, 0);
            // result[0] = 0;
            if (num == 0) return result;
            for (int i = 1; i < size; ++i) {
                result[i] = result[i >> 1] + (i & 1);
            }
            return result;
        }
};



int main() {

	Solution s;

	return 0;
}
