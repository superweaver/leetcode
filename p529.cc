#include "common.h"

class Solution {
  public:
      // 'M' represents an unrevealed mine;
      // 'E' represents an unrevealed empty square;
      // 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines;
      // digit ('1' to '8') represents how many mines are adjacent to this revealed square;
      // and finally 'X' represents a revealed mine.
    // https://www.cnblogs.com/grandyang/p/6536694.html
    // non-recursive solution
    // if the clicked position is mine(M), mark it as "X" and return;
    // otherwise the clicked position is a unrevealed empty "E"
    // count the number of mines in its neighbors and mark the clicked position as that number
    // if # is zero, do same thing for its neighbors
    // note that in the procedure, record neighbors (#==0 and neighbor is E)
    // if finally the # is zero, then update its neighbor
    // update means expand known information
    
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click) {
        // non-recursive
        if (board.empty() || board[0].empty()) {
            return {};
        }
        int m = board.size();
        int n = board[0].size();
        int r = click[0];
        int c = click[1];
        queue<pair<int, int>> q;
        q.push(make_pair(r, c));
        while (!q.empty()) {
            auto p = q.front();
            r = p.first;
            c = p.second;
            q.pop();
            if (board[r][c] == 'M') {
                // this is a mine, no more information can be deduced
                board[r][c] = 'X';
                return board;
            } else {
                // this is a "E"
                vector<pair<int, int>> next; // store the coordinates of adjacent unrevealed square 'E'

                int count = 0; // # of mine in the 3 by 3 region (or smaller because of board boundary)
                for (int i = -1; i < 2; ++i) {
                    for (int j = -1; j < 2; ++j) {
                        int x = r + i;
                        int y = c + j;
                        if (x < 0 || x >= m || y < 0 || y >= n) {
                            continue;
                        }
                        if (board[x][y] == 'M') {
                            count++;
                        }
                        // 'E' means unrevealled , not touched in previous searches
                        if (count == 0 && board[x][y] == 'E') {
                            next.push_back({x, y});
                        }
                    }
                }
                if (count) {
                    // this is an revealed square with this much adjacent mines
                    //
                    // if Mine exists in neighbor, no need to updae neighbors
                    // note next may not be empty at this time
                    board[r][c] = count + '0';
                } else {
                    // this is an revealed square with no adjacent mine
                    board[r][c] = 'B'; // this is only true for (r,c)

                    // for the neighbors, we don't know the final information for them
                    // now just mark them as 'B';
                    for (auto &v : next) {
                        // note !!!
                        board[v.first][v.second] = 'B'; // temporary mark, avoid repeatted push
                        q.push(v);
                    }
                }
            }
        }
        return board;
    }
};

int main() {

    Solution s;

    return 0;
}
