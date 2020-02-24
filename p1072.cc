#include "common.h"
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix)
    {
        int m = matrix.size();
		// count
		// order of column doesn't matter
		// order of row doesn't matter
		int result = 0;
        unordered_map<string, int> count;
        for (int i = 0; i < m; ++i) {
			string str;
			string str_p;
			for(auto j : matrix[i]) {
                str.push_back('0' + j);
				str_p.push_back('0' + 1 - j);
            }
            int n_str = ++count[str];
			int n_str_p = count.count(str_p) ?  count[str_p]: 0;
			result = max(result, n_str + n_str_p);
		}
		return result;
   }
};

int main()
{

    vector<vector<int>> matrix{ { 0, 1 }, { 1, 1 } }; // 1
    matrix = { { 0, 1 }, { 1, 0 } }; // 2
	matrix = {{0,0,0},{0,0,1},{1,1,0}}; // 2

    Solution s;

	cout << s.maxEqualRowsAfterFlips(matrix) << endl;
    return 0;
}
