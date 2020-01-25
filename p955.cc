#include "common.h"
class Solution {
    public:
        int minDeletionSize(vector<string>& A) {
            int m = A.size();
            int n = A[0].size();
            set<int> columns;
            for (int i = 0; i < n; ++i) {
                columns.insert(i);
            }
            helper(A, columns, 0, m, 0);
            return n - columns.size();
        }
    private:
        void helper(vector<string>& A, set<int>& columns, int row_begin, int row_end, int column) {
            // row_end is exclusive
            if (row_end == row_begin + 1) {
                return;
            }
            if (columns.empty()) {
                return ;
            }
            auto it = columns.lower_bound(column);
            if (it == columns.end()) {
                return ;
            } 
            column = *it;
            for (int r = row_begin; r < row_end;) {
                int next_r = r + 1;
                while( next_r < row_end && A[r][column] == A[next_r][column]) {
                   next_r++; 
                }
                helper(A, columns, r, next_r, column + 1);
                if (next_r < row_end) {
                    if ( A[r][column] > A[next_r][column]) {
                        columns.erase(column);
                        helper(A,columns, row_begin, row_end, column + 1); // continue to process other column;
                        return ;
                    }
                }
                r = next_r;
            }
        }
        
};

int main() {
    vector<string> A = {"zyx","wvu","tsr"}; // 3
    A = {"xc","yb","za"};  // 0
    A = {"ca","bb","ac"};  // 1
    Solution s;
    cout << s.minDeletionSize(A) << endl;
    return 0;
}
