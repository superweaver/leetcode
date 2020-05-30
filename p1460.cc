#include "common.h"
class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> count;
        for (auto i : target) {
            count[i]++;
        }

        for (auto i : arr) {
            if (--count[i] < 0) {
                return false;
            }
        }
        return true;
    }
};

int main() {

	Solution s;

	return 0;
}
