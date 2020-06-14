#include "common.h"
// https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/discuss/303847/Simple-C%2B%2B-Solution-with-comments
class Solution_ref {
  public:
    int maxEqualRowsAfterFlips(vector<vector<int>> &matrix) {
        unordered_map<string, int> hmap;
        for (auto x : matrix) {
            string s = "";
            //s keeps track of relative ordering of elements in a row w.r.t the first element
            int top = x[0];
            for (int i = 0; i < x.size(); i++) {
                if (x[i] == top)
                    s += '1';
                else
                    s += '0';
            }
            hmap[s]++;
        }

        int result = 0;
        for (auto &p : hmap)
            result = max(result, p.second);
        //rows that have identical relative ordering, can be simultaneously toggled columnwise in order to make all
        //elements of any of those rows unique. So the answer is maximum number of rows with identical relative ordering.
        return result;
    }
};

class Solution {
  public:
    int maxEqualRowsAfterFlips(vector<vector<int>> &matrix) {
        int m = matrix.size();
        // count
        // order of column doesn't matter
        // order of row doesn't matter
        int result = 0;
        unordered_map<string, int> count;
        for (int i = 0; i < m; ++i) {
            string str;
            string str_p;
            for (auto j : matrix[i]) {
                str.push_back('0' + j);
                str_p.push_back('0' + 1 - j);
            }
            int n_str = ++count[str];
            int n_str_p = count.count(str_p) ? count[str_p] : 0;
            result = max(result, n_str + n_str_p);
        }
        return result;
    }
};

int main() {

    vector<vector<int>> matrix{{0, 1}, {1, 1}}; // 1
    matrix = {{0, 1}, {1, 0}};                  // 2
    matrix = {{0, 0, 0}, {0, 0, 1}, {1, 1, 0}}; // 2

    Solution s;

    cout << s.maxEqualRowsAfterFlips(matrix) << endl;
    return 0;
}
