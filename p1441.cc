#include "common.h"
class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> result;
        // n is not used
        if (target.empty()) {
           for (int i = 0; i < n; ++i) {
                result.push_back("Push");
                result.push_back("Pop");
           }
           return result;
        }
        int listfront = 1;
        for (size_t i = 0; i < target.size(); ++i) {
            while (listfront < target[i]) {
                result.push_back("Push");
                result.push_back("Pop");
                listfront++;
            }
            // listfront == target[i]
            result.push_back("Push");
            listfront++;
        }
        return result;
    }
};

int main() {
    int n = 3;
    vector<int> target{1,3};

	Solution s;
    displayvector(s.buildArray(target, n));

	return 0;
}
