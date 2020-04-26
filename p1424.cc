#include "common.h"
#include <cstdio>
class Solution {
public:

    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<vector<int>> result;
        size_t n = nums.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < nums[i].size(); ++j) {
                auto index = i + j; 
                if (index == result.size()) {
                    result.push_back({});
                }
                result[index].push_back(nums[i][j]);
            }
        }
        vector<int> r;
        for(auto&v : result) {
            reverse(v.begin(), v.end());
            r.insert(r.end(), v.begin(), v.end());
        }
        return r;
    }

    vector<int> findDiagonalOrder2(vector<vector<int>>& nums) {
		int n = nums.size();
        int maxIndex = 0;
		for (int i = 0; i < n; ++i) {
			maxIndex = max(maxIndex, i + (int)nums[i].size());
        }
		vector<int> result;
		for(int i = 0; i <= maxIndex; ++i)
		{
			int col = 0;
			int row = i - 0;
			while(row >= 0)
			{
				if(col < nums[row].size())
				{
					result.push_back(nums[row][col]);
				}
				col++;
				row = i - col;
			}
		}
        return result;
	}
};

int main() {
    vector<vector<int>>  nums = {{1,2,3},{4,5,6},{7,8,9}};
	nums = {{1, 2, 3, 4, 5}, {6, 7}, {8}, {9, 10, 11}, {12, 13, 14, 15, 16}};

	Solution s;
    auto r = s.findDiagonalOrder(nums);
    displayvector(r);

	return 0;
}
