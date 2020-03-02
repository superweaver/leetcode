#include "common.h"
class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		int left = 0;
		int result = 0;
		for (int i = m - 1; i >= 0; --i) {
			auto &v = grid[i];
            while (left < n && v[left] >= 0) {
                left++;
            }
			result += (n - left);
        }
		return result;
    }
};

int main() {

	Solution s;

	return 0;
}
