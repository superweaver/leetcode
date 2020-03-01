#include "common.h"
class Solution {
public:
    vector<int> sumZero(int n) {
        int half = n / 2;
        vector<int> result;
        for (int i = 1; i <= half; ++i){
            result.push_back(i);
            result.push_back(-i);
        }
        if (n&1){
            result.push_back(0);
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
