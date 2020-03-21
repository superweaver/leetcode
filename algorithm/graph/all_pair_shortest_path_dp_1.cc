#include "../../../common.h"
class Solution {
public:
    Solution()
    {
        initilize();
    }
    void slow_all_pair_shortest_path()
    {
        int n = d_size;
        auto L = W;                    // L(1)
        for (int m = 2; m < n; ++m) {  // m : at most m edges
            L = extend(L, W);
        }
        for (auto& v : L) {
            displayvector(v);
        }
    }
    void faster_all_pair_shortest_path()
    {
        int n = d_size;
        auto L = W;  // L(1)
        int m = 1;
        while (m < n - 1) {
            L = extend(L, L);  // L(2), L(4) , ... L(2^m)
			m <<= 1;
        }
        // 2^m >= n-1
        for (auto& v : L) {
            displayvector(v);
        }
    }

private:
    int d_size;
    vector<vector<int>> W;
    vector<vector<int>> extend(const vector<vector<int>>& L, const vector<vector<int>>& W)
    {
        int n = L.size();
        vector<vector<int>> result(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // result[i][j] = INF
                for (int k = 0; k < n; ++k) {
					if (L[i][k] != INT_MAX && W[k][j] != INT_MAX) { // !!!! important
                        result[i][j] = min(result[i][j], L[i][k] + W[k][j]);
                    }
                }
            }
        }
        return result;
    }
    void initilize()
    {
        // refer to Figure 25.2
        d_size = 6;
        W = vector<vector<int>>(d_size, vector<int>(d_size, INT_MAX));
        W[0][4] = -1;

        W[1][0] = 1;
        W[1][3] = 2;

        W[2][1] = 2;
        W[2][5] = -8;

        W[3][0] = -4;
        W[3][4] = 3;

        W[4][1] = 7;

        W[5][1] = 5;
        W[5][2] = 10;
		for (int i = 0 ; i < d_size; ++i) {
			W[i][i] = 0;
		}
    }
};
int main()
{
    Solution s;
    s.slow_all_pair_shortest_path();
	cout << endl;
    s.faster_all_pair_shortest_path();
}
