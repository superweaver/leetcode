#include "common.h"
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		int step = 0;
		const int mask = 1 << 16;
        vector<vector<int>> dirs = {{}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
		int r = 0;
		int c = 0;
		queue<int> q;
		q.push(r * n + c);
		grid[r][c] |= mask; // visited;
		while(true) {
            //unordered_set<int> next;
			queue<int> next;
            while(!q.empty()) {
				auto current = q.front();
				q.pop();
				r = current / n;
				c = current % n;
				if (r == m - 1 && c == n - 1) {
					return step;
				}
				/*
				if (next.count(current)) { // use grid to mark 
					next.erase(current);
				}
				*/
				for (int d = 1 ; d < 5; ++d) {
					int nr = r + dirs[d][0];
					int nc = c + dirs[d][1];
					if (nr < 0 || nc < 0 || nr >= m || nc >= n) {
						continue;
					}
                    if (!(grid[nr][nc] & mask)) {
                        if (d == (grid[r][c] & 0xFFFF)) {
                            q.push(nr * n + nc);
                            grid[nr][nc] |= mask;
                        } else {
							//next.insert(nr * n + nc);
                            next.push(nr * n + nc);
                        }
                    }
                }
			}
			// include next into q;
            //for (auto p : next) {
			while(!next.empty()) {
				auto p = next.front();
				next.pop();
                r = p / n;
                c = p % n;
				if (grid[r][c] & mask) {
					continue;
				}
                q.push(p);
                grid[r][c] |= mask;
            }
			step++;
        }
		return 0;
	}
};

class Solution_ref {
public:
    int minCost(vector<vector<int>>& grid) {
        int R = grid.size();
        int C = grid[0].size();

        vector<vector<bool>> visited(R, vector<bool>(C, false));

        queue<int> q;
        int res = 0;
        q.push(R * C - 1);
        visited[R - 1][C - 1] = true;
        static const int dxdys[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

		// layer by layer
        while (true) {
            queue<int> frontier;
            while (!q.empty()) {
                frontier.push(q.front());
                int r = q.front() / C;
                int c = q.front() % C;
                if (r == 0 && c == 0) {
                    return res;
                }
                q.pop();
                for (auto dxdy : dxdys) {
                    int x = r + dxdy[0];
                    int y = c + dxdy[1];
                    if (x < 0 || x >= R || y < 0 || y >= C) {
                        continue;
                    }
                    if (visited[x][y] == true) {
                        continue;
                    }
                    int dir = grid[x][y] - 1;
                    if ((x + dxdys[dir][0]) == r && (y + dxdys[dir][1]) == c) {
                        q.push(x * C + y);
                        visited[x][y] = true;
                    }
                }
            }
            ++res;
            while (!frontier.empty()) {
                int r = frontier.front() / C;
                int c = frontier.front() % C;
                frontier.pop();
                for (auto dxdy : dxdys) {
                    int x = r + dxdy[0];
                    int y = c + dxdy[1];
                    if (x < 0 || x >= R || y < 0 || y >= C) {
                        continue;
                    }
                    if (visited[x][y] == true) {
                        continue;
                    }
                    q.push(x * C + y);
                    visited[x][y] = true;
                }
            }
        }
        return -1;
    }
};

class Solution_my {
public:
	int minCost(vector<vector<int>>& grid) {
        // at most there are m * n * 4 states
        // cost is at most m + n - 1
        // encode =  (steps << 20) +  (dir << 16)  + r * n + c>
        vector<vector<int>> dirs = {{}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
		priority_queue<int, vector<int>, greater<int>> q;
        int m = grid.size();
        int n = grid[0].size();
        int r = 0;
        int c = 0;
        int d = grid[r][c] & 0xFFFF;

		auto encode = [n](int s, int d, int r, int c) {return (s << 20) + (d << 16) + r * n + c;};
		q.push(encode(0, d, r, c));
        while (!q.empty()) {
            auto p = q.top();
			q.pop();
            int step = p >> 20;
            int dir = 0x7 & (p >> 16);  // current dir
            p &= 0xFFFF;
            r = p / n;
            c = p % n;
            if (r == m - 1 && c == n - 1) {
                return step;
            }
            for (int d = 1; d <= 4; ++d) { 
                if (d == dir) {
					// go 
                    int next_r = r + dirs[d][0];
                    int next_c = c + dirs[d][1];
                    if (!(next_r < 0 || next_c < 0 || next_r >= m || next_c >= n)) {
                        int nextd = grid[next_r][next_c] & 0xFFFF;  // next node's dir
                        int mask = 1 << (nextd + 16);
                        if (!(grid[next_r][next_c] & mask)) {
                            grid[next_r][next_c] |= mask;
                            q.push(encode(step, nextd, next_r, next_c));
                        }
                    }
                    continue;
                } else { 
					// change dir
                    int next_r = r;
                    int next_c = c;
                    int mask = 1 << (d + 16);
                    if (grid[next_r][next_c] & mask) {
                        continue;
                    } else {
                        grid[next_r][next_c] |= mask;
                        q.push(encode(step + 1, d, next_r, next_c));
                    }
                }
            }
        }
        return 0;
    }
};

int main() {

    vector<vector<int>> grid = { { 1, 1, 1, 1 }, { 2, 2, 2, 2 }, { 1, 1, 1, 1 }, { 2, 2, 2, 2 } }; // 3
	grid = {{1,1,3},{3,2,2},{1,1,4}}; // 0
    grid = { { 1, 2 }, { 4, 3 } }; // 1
	grid = {{2,2,2},{2,2,2}}; // 3
	//grid = {{4}}; // 0
    Solution s;
	cout << s.minCost(grid) << endl;
	//cout << s.minCost_2(grid) << endl;

    return 0;
}
