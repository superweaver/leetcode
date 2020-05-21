#include "common.h"
class Solution {

    // for 2D matrix, use rowSum  or colSum to reduce dimension
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(); // row
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size(); // col
        // column pair i, j
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            vector<int> rowSum(m, 0); // store the sum in r between column pair [i, j]
            for (int j = i; j < n; ++j) {
                int CurrentSum = 0; // store the sum of rectangle  between [0, i] to [r, j]
                set<int> s;
                // nice trick
                s.insert(0);    // key !!
                for (int r = 0; r < m; r++) {
                    rowSum[r] += matrix[r][j];
                    CurrentSum += rowSum[r];
                    // note: even CurrentSum < k, that does't mean
                    // there is no submatrix from K to r that satisfies
                    // sum <= k

                    // check if there is a row K to fulfill that
                    // from row K + 1 to row r, colum i to current j
                    // the sum is <= k
                    auto it = s.lower_bound(CurrentSum - k);
                    if (it != s.end()) {
                        result = max(result, CurrentSum - *it);
                    }
                    s.insert(CurrentSum);
                }
            }
        }
        return result;
    }
};


int main() {

	Solution s;

	return 0;
}
