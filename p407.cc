#include "common.h"
// not solved;
// http://www.cnblogs.com/grandyang/p/5928987.html
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int result = 0;
        int m = heightMap.size();
        if (m == 0) {
            return result;
        }
        int n = heightMap[0].size();
        if (n == 0) {
            return result;
        }
        int level = INT_MIN;
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        // add the boundary to q;
        int i = 0;
        int j = 0;
        for (j = 0; j < n; ++j) {
            if(!visited[i][j]) {
                q.push(make_pair(heightMap[i][j], i * n + j));
                visited[i][j] = true;
            }
        }
        i = m - 1;
        for (j = 0; j < n; ++j) {
            if(!visited[i][j]) {
                q.push(make_pair(heightMap[i][j], i * n + j));
                visited[i][j] = true;
            }
        }
        j = 0;
        for (i = 0; i < m; ++i) {
            if (!visited[i][j]) {
                q.push(make_pair(heightMap[i][j], i * n + j));
                visited[i][j] = true;
            }
        }
        j = n - 1;
        for (i = 0; i < m; ++i) {
            if (!visited[i][j]) {
                q.push(make_pair(heightMap[i][j], i * n + j));
                visited[i][j] = true;
            }
        }
        vector<vector<int> > dir = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

        while(!q.empty()) {
            auto p = q.top();
            q.pop();
            int c = p.second % n;
            int r = p.second / n;
            level = max(level, heightMap[r][c]);
            // check top/bottom/left/right of r,c
            for (int i = 0; i < 4; ++i) {
                int rp = r + dir[i][0];
                int cp = c + dir[i][1];
                if (rp < 0 || rp >= m || cp < 0 || cp >= n || visited[rp][cp]) {
                    continue;
                }
                if (heightMap[rp][cp] < level) {
                    result += level - heightMap[rp][cp]; // key is to use level to minus h
                }
                q.push(make_pair(heightMap[rp][cp], rp * n + cp));  // water now is treated as wall
                visited[rp][cp] = true;

            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
