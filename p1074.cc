#include "common.h"
class Solution {
public:
	// http://www.noteanddata.com/leetcode-1074-Number-of-Submatrices-That-Sum-to-Target-java-solution-note.html
	// dimension reduction
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target)
    {
        // similar to prefix sum in 2d
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> prefix_sum(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] -
                                   prefix_sum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
		int result = 0;
		// pick any of two column [i, j)
		for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
				// form a new 1d array
				vector<int> band; // cover column i to column j [i, j)
                for (int k = 0; k <= m; ++k) {
					band.push_back(prefix_sum[k][j] - prefix_sum[k][i]);
				}
				// note : band is already prefix sum
				result += helper(band, target);	
            }
        }
		return result;
    }
private:
	int helper(vector<int>& band, int target) {
		// return how many subarry with sum == target
		unordered_map<int, int> cache;	
		int count = 0;
		for (auto i : band) {
            if (cache.count(i - target)) {
                count += cache[i - target];
            }
            cache[i]++;
        }
		return count;
	}
};

int main()
{

    vector<vector<int>> matrix = { { 0, 1, 0 }, { 1, 1, 1 }, { 0, 1, 0 } };
    int target = 0;

	matrix = {{0,1,1,1,0,1},{0,0,0,0,0,1},{0,0,1,0,0,1},{1,1,0,1,1,0},{1,0,0,1,0,0}};
	target = 0;

    Solution s;
	cout << s.numSubmatrixSumTarget(matrix, target) << endl;
    return 0;
}

