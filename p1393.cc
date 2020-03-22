#include "common.h"
class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<pair<int, int>> road(6);
        road[0] = { 1, 3 };  // right, left
        road[1] = { 0, 2 };  // top, bottom
        road[2] = { 2, 3 };  // bottom, left
        road[3] = { 1, 2 };  // bottom, right;
        road[4] = { 0, 3 };  // top, left
        road[5] = { 0, 1 };  // top, right;

        int current = road[grid[0][0] - 1].first;  //
        int r = 0;
        int c = 0;
        if (walk(grid, r, c, current, m, n, road)) {
            return true;
        }
        current = road[grid[0][0] - 1].second;
        if (walk(grid, r, c, current, m, n, road)) {
            return true;
        }
        return false;
    }

private:
    vector<int> current2next{ 2, 3, 0, 1 };
    vector<vector<pair<int, int>>> dirs = {
        { { 0, -1 }, { 1, 0 }, { 0, -1 }, { 1, 0 }, { 0, -1 }, { 0, 1 } },  // first to second
        { { 0, 1 }, { -1, 0 }, { 1, 0 }, { 0, 1 }, { -1, 0 }, { -1, 0 } }   // secodn to first
    };

    bool walk(vector<vector<int>>& grid, int r, int c, int current, int m, int n,
              vector<pair<int, int>>& road)
    {
        while (true) {
            int path = grid[r][c] - 1;
            if (current == road[path].first || current == road[path].second) {
                if (r == m - 1 && c == n - 1) {
                    return true;
                }
                bool flag = (current == road[path].first);  // first -> second
                                                            // next node
                current = current2next[flag ? road[path].second : road[path].first];
                // update r, c
                r += dirs[!flag][path].first;
                c += dirs[!flag][path].second;
                if (r < 0 || c < 0 || r >= m || c >= n) {
                    return false;
                }
            } else {
                return false;
            }
        }
    }
};

int main()
{
    vector<vector<int>> grid = { { 2, 4, 3 }, { 6, 5, 2 } }; // 1
	grid = {{1,2,1},{1,2,1}}; // 0
	grid = {{1,1,2}}; // 0
	grid = {{1,1,3}}; // 0
	grid = {{2},{2},{2},{2},{2},{2},{6}}; // 1

    Solution s;
    cout << s.hasValidPath(grid) << endl;

    return 0;
}
