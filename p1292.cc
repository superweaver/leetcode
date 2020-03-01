#include "common.h"
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold)
    {
        int m = mat.size();
        int n = mat[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            int pre = 0;
            for (int j = 0; j < n; ++j) {
                pre = (mat[i][j] += pre + (i > 0 ? mat[i - 1][j] : 0) -
                                    ((i > 0 && j > 0) ? mat[i - 1][j - 1] : 0));
                // check len == result + 1
                // top left
                while (true) {
                    int len = result + 1;
                    int r = i - len + 1;
                    if (r < 0) {
                        break;
                    }
                    int c = j - len + 1;
                    if (c < 0) {
                        break;
                    }
                    int sum = mat[i][j] - (r == 0 ? 0 : mat[r - 1][j]) -
                              (c == 0 ? 0 : mat[i][c - 1]) +
                              ((r == 0 || c == 0) ? 0 : mat[r - 1][c - 1]);
                    if (sum <= threshold) {
                        result = len;
                    } else {
						break;
					}
                }
            }
        }
        return result;
    }
};

int main()
{

    vector<vector<int>> mat = { { 1, 1, 3, 2, 4, 3, 2 },
                                { 1, 1, 3, 2, 4, 3, 2 },
                                { 1, 1, 3, 2, 4, 3, 2 } };
    int threshold = 4; // 2
//	mat = {{2,2,2,2,2},{2,2,2,2,2},{2,2,2,2,2},{2,2,2,2,2},{2,2,2,2,2}}, threshold = 1;// 0
    mat = { { 1, 1, 1, 1 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 } }, threshold = 6; // 3
	mat = {{18,70},{61,1},{25,85},{14,40},{11,96},{97,96},{63,45}}, threshold = 40184; // 2


    Solution s;
	cout << s.maxSideLength(mat, threshold) << endl;
    return 0;
}

