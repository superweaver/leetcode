#include "common.h"
// https://www.cnblogs.com/grandyang/p/9053705.html
// https://leetcode.com/problems/transform-to-chessboard/discuss/132113/Java-Clear-Code-with-Detailed-Explanations
class Solution {
public:
    int movesToChessboard(vector<vector<int> >& board)
    {
        int n = board.size();
        // for any rectangle with (0, 0), its four vertex, its four vertices must be
        // 1) four 1
        // 2) four 0
        // 3) two 1 and two 0
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[0][0] ^ board[0][j] ^ board[i][j] ^ board[i][0] == 1) {
                    return -1;
                }
            }
        }
        int r0ones = 0;
        int c0ones = 0;
        // take 10101xx as standard checkboard
        int rowDiff = 0;
        int columnDiff = 0;
        for (int i = 0; i < n; ++i) {
            r0ones += board[0][i];
            c0ones += board[i][0];
            // how many places are different from standard
            rowDiff += ((i & 1) ^ board[0][i]);
            columnDiff += ((i & 1) ^ board[i][0]);
        }
        if (r0ones < n / 2 || r0ones > (n +1)/ 2) {
            return -1;
        }
        if (c0ones < n / 2 || c0ones > (n+1) / 2) {
            return -1;
        }

        if (n & 1) {
            // for odd n
            // the diff must be even, since each swap will increase/decrease two diff
            if (rowDiff & 1) {
                rowDiff = n - rowDiff;
            }
            if (columnDiff & 1) {
                columnDiff = n - columnDiff;
            }
        } else {
            // for even n
            // diff = min (diff, n - diff)
            rowDiff = min(rowDiff, n - rowDiff);
            columnDiff = min(columnDiff, n - columnDiff);
        }
        return (rowDiff + columnDiff) / 2;
    }
};


int main() {

	Solution s;

	return 0;
}
