#include "common.h"
class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid)
    {
        // state = (i, j, h/v)
        int n = grid.size();
        // use upper 16bit to reprsent if it has been visited
        // bit16 -> h
        // bit17 -> v
        const int Lower = 0xFFFF;
        const int hmark = 1 << 16;
        const int testh = hmark | Lower;
        const int vmark = 1 << 17;
        const int testv = vmark | Lower;
        queue<int> q;
        grid[0][0] |= hmark;
		// encode (h << 16) + r *n + c
        auto encode = [n](int r, int c, int h) { return (h << 16) + r * n + c; };
        q.push(encode(0, 0, 1));
        int moves = 0;
        while (!q.empty()) {
            auto sizes = q.size();
            while (sizes--) {
                auto current = q.front();
                q.pop();
                int h = current >> 16;
                current &= Lower;
                int r = current / n;
                int c = current % n;
                if (r == n - 1 && c == n - 2 && h) {
                    return moves;
                }
                // what is next?
                if (h) {
                    // h
                    if (c + 2 < n && !(grid[r][c + 2] & Lower) && !(grid[r][c + 1] & testh)) {
                        q.push(encode(r, c + 1, h));
                        grid[r][c + 1] |= hmark;
                    }
                    // v
                    if (r + 1 < n && !(grid[r + 1][c] & Lower) && !(grid[r + 1][c + 1] & Lower) &&
                        !(grid[r + 1][c] & testh)) {
                        q.push(encode(r + 1, c, h));
                        grid[r + 1][c] |= hmark;
                    }
                    // rotate
					// Rotate clockwise if it's in a horizontal position and the two cells under it are both empty.
					// two cells are empty !!!
                    if (r + 1 < n && !(grid[r + 1][c] & Lower) && !(grid[r + 1][c + 1] & Lower) &&
                        !(grid[r][c] & testv)) {
                        q.push(encode(r, c, 1 - h));
                        grid[r][c] |= vmark;
                    }
                } else {
                    // h
                    if (c + 1 < n && !(grid[r][c + 1] & Lower) && !(grid[r + 1][c + 1] & Lower) &&
                        !(grid[r][c + 1] & testv)) {
                        q.push(encode(r, c + 1, h));
                        grid[r][c + 1] |= vmark;
                    }
                    // v
                    if (r + 2 < n && !(grid[r + 2][c] & Lower) && !(grid[r + 1][c] & testv)) {
                        q.push(encode(r + 1, c, h));
                        grid[r + 1][c] |= vmark;
                    }
                    // rotate
                    if (c + 1 < n && !(grid[r][c + 1] & Lower) && !(grid[r + 1][c + 1] & Lower) &&
                        !(grid[r][c] & testh)) {
                        q.push(encode(r, c, 1 - h));
                        grid[r][c] |= hmark;
                    }
                }
            }
            moves++;
        }
        return -1;
    }
};

int main()
{

    vector<vector<int>> grid = {
        { 0, 0, 0, 0, 0, 1 }, { 1, 1, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 1 },
        { 0, 0, 1, 0, 1, 0 }, { 0, 1, 1, 0, 0, 0 }, { 0, 1, 1, 0, 0, 0 }
    };  // 11
    grid = { { 0, 0, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1, 1 }, { 1, 1, 0, 0, 0, 1 },
             { 1, 1, 1, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1 }, { 1, 1, 1, 0, 0, 0 } };  // 9

    grid = { { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
             { 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
             { 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
             { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
             { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
             { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
             { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
             { 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
             { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
             { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
             { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
             { 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
             { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
             { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
             { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


    Solution s;
	cout << s.minimumMoves(grid) << endl;
    return 0;
}
