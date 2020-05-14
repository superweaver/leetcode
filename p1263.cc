#include "common.h"
class DisjointSet {
    public:
        DisjointSet(int n) {
            sizes.assign(n, 1);
            parent.resize(n);
            for (int i = 0; i < n; ++i) {
                parent[i] = i;     
            }
        }
        int Find(int node) {
            while (node != parent[node]) {
                parent[node] = parent[parent[node]];
                node = parent[node];
            }
            return node;
        }
        bool sameGroup(int u, int v) {
            return Find(u) == Find(v);
        }
        bool Union(int u, int v) {
            int uid = Find(u);
            int vid = Find(v);
            if (uid == vid) {
                return false;
            }
            if (sizes[uid] < sizes[vid]) {
                swap(uid, vid);
            }
            // sizes[uid] >= sizes[vid]
            sizes[uid] += sizes[vid];
            parent[vid] = uid;
            return true;
        }
    private:
        vector<int> parent;
        vector<int> sizes;
};

class Solution_my {
  public:
    int minPushBox(vector<vector<char>> &grid) {
        // bfs
        // state = box's position +  person's position
        // 1 <= m <= 20
        // 1 <= n <= 20
        // (i, j) + person's relative pos
        // totally
        _grid = grid;
        int m = grid.size();
        int n = grid[0].size();
        _n = n;
        _m = m;
        int total = m * n;
        pair<int, int> posB, posS, posT;

        DisjointSet ds(total);
        vector<bool> visited(m * n * m * n, false); 
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'B') {
                    posB = {i, j};
                    _grid[i][j] = '.';
                }
                if (grid[i][j] == 'S') {
                    posS = {i, j};
                    _grid[i][j] = '.';
                    grid[i][j] = '.';
                }
                if (grid[i][j] == 'T') {
                    posT = {i, j};
                    grid[i][j] = '.';
                }
                if (grid[i][j] == '.') {
                    if (i > 0 && grid[i - 1][j] == '.') {
                        ds.Union(getkey(i - 1, j), getkey(i, j));
                    }
                    if (j > 0 && grid[i][j - 1] == '.') {
                        ds.Union(getkey(i, j - 1), getkey(i, j));
                    }
                    if (i + 1 < _m && grid[i + 1][j] == '.') {
                        ds.Union(getkey(i + 1, j), getkey(i, j));
                    }
                    if (j + 1 < _n && grid[i][j + 1] == '.') {
                        ds.Union(getkey(i, j + 1), getkey(i, j));
                    }
                }
            }
        }

        if (!ds.sameGroup(getkey(posS.first, posS.second), getkey(posT.first, posT.second))) {
            return -1;
        }

        queue<pair<int, int>> q;
        for (int k = 0; k < 4; ++k) {
            int pi = posB.first + dirs[k];
            int pj = posB.second + dirs[k + 1];
            if (pi < 0 || pj < 0 || pi >= m || pj >= n) {
                continue;
            }
            if (grid[pi][pj] != '#') {
                // check if you can get it from position s to [pi, pj]
                if (ds.sameGroup(getkey(posS.first, posS.second), getkey(pi, pj))) {
                    int keyB = getkey(posB.first, posB.second);
                    int keyij = getkey(pi, pj);
                    q.push({keyB, keyij});
                    visited[keyB * total + keyij] = true;
                }
            }
        }
        
        int step = 0;
        while (!q.empty()) {
            auto s = q.size();
            while (s--) {
                auto c = q.front();
                q.pop();
                auto pb = getrc(c.first);
                auto ps = getrc(c.second);
                //cout << pb.first << " : " << pb.second << " <- "  << ps.first << " : " << ps.second << endl;
                if (pb == posT) {
                    return step;
                }
                // check if you can push
                auto nbr = pb.first * 2 - ps.first;   // next box row
                auto nbc = pb.second * 2 - ps.second; // next box column
                if (nbr < 0 || nbc < 0 || nbr >= m || nbc >= n) {
                    continue;
                }
                if (_grid[nbr][nbc] == '#') {
                    continue;
                }
                // can push there
                _grid[nbr][nbc] = 'B';
                // check three or four near by slots
                DisjointSet ds(total);
                updateDisjointSet(ds);
                ps = pb;
                pb = {nbr, nbc};
                auto keypb = getkey(pb.first, pb.second);
                auto keyps = getkey(ps.first, ps.second);
                q.push({keypb, keyps});
                visited[keypb * total + keyps] = true;
                //if (keypb * total + keyps >= visited.size()) { cout << "Error" << endl; }
                for (int k = 0; k < 4; ++k) {
                    int row = pb.first + dirs[k];
                    int col = pb.second + dirs[k+1];
                    if (row < 0 || col < 0 || row >= m || col >= n) {
                        continue;
                    }
                    if (row == ps.first && col == ps.second) {
                        continue;
                    }
                    if (_grid[row][col] == '.') {
                        // check if we can go there
                        auto keyps_p = getkey(row, col);
                        if (ds.sameGroup(keyps, keyps_p)) {
                            if (visited[keypb * total + keyps_p] == false) {
                                visited[keypb * total + keyps_p] = true;
                                q.push({keypb, keyps_p});
                            }
                        }
                    }
                }
                _grid[nbr][nbc] = '.';
            }
            step++;
        }
        return -1;
    }

  private:
    vector<int> dirs = {0, 1, 0, -1, 0};
    vector<vector<char>> _grid;
    int _n;
    int _m;
    inline int getkey(int i, int j) { return i * _n + j; }
    inline pair<int, int> getrc(int key) { return {key / _n, key % _n}; }
    void updateDisjointSet(DisjointSet & ds) {
        for (int i = 0; i < _m; ++i) {
            for (int j = 0; j < _n; ++j) {
               if (_grid[i][j] == '.') {
                   if (i > 0 && _grid[i - 1][j] == '.') {
                       ds.Union(getkey(i - 1, j), getkey(i, j));
                   }
                   if (j > 0 && _grid[i][j - 1] == '.') {
                       ds.Union(getkey(i, j - 1), getkey(i, j));
                   }
                   if (i + 1 < _m && _grid[i + 1][j] == '.') {
                       ds.Union(getkey(i + 1, j), getkey(i, j));
                   }
                   if (j + 1 < _n && _grid[i][j + 1] == '.') {
                       ds.Union(getkey(i, j + 1), getkey(i, j));
                   }
               }
            }
        }
    }
};

struct Node {
    int bx; // box x
    int by; // box y
    int px; // person x
    int py; // person y
    int h;  // manhaton distance to T
    int g;  // steps has walked

    // (i-1, j) (i, j) // bx - px + 1 = 2  // ((by - py) + 1) >> 1 = 1 >> 1 = 0
    // (i+1, j) (i, j) // bx - px + 1 = 0  // ((by - py) + 1) >> 1 = 1 >> 1 = 0
    // (i, j-1) (i, j) // bx - px + 1 = 1  // ((by - py) + 1) >> 1 = 2 >> 1 = 1
    // (i, j+1) (i, j) // bx - px + 1 = 1  // ((by - py) + 1) >> 1 = 0 >> 1 = 0
    int key() const { return ((by * m + bx) << 2) | ((bx - px) + 1) | ((by - py) + 1) >> 1; }
    int f() const { return g + h; } // this is the key
    bool operator<(const Node &o) const { return f() > o.f(); }

    static int m;
};

int Node::m;

class Solution {
  public:
    int minPushBox(vector<vector<char>> &grid) {
        const vector<int> dirs{0, -1, 0, 1, 0};
        const int n = grid.size();
        const int m = Node::m = grid[0].size();
        Node start;
        Node end;

        for (int y = 0; y < n; ++y)
            for (int x = 0; x < m; ++x)
                if (grid[y][x] == 'B') {
                    start.bx = x;
                    start.by = y;
                } else if (grid[y][x] == 'S') {
                    start.px = x;
                    start.py = y;
                } else if (grid[y][x] == 'T') {
                    end.bx = x;
                    end.by = y;
                }

        auto isValid = [&](int x, int y) {
            return !(x < 0 || x >= m || y < 0 || y >= n || grid[y][x] == '#');
        };

        auto hasPath = [&](const Node &cur, int tx, int ty) {
            // check if you can go from current to tx ty (next person's pos)
            if (!isValid(tx, ty))
                return false;
            vector<int> seen(m * n);
            queue<int> q;
            q.push(cur.py * m + cur.px);
            seen[cur.py * m + cur.px] = 1;
            while (q.size()) {
                int x = q.front() % m;
                int y = q.front() / m;
                q.pop();
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i];
                    int ny = y + dirs[i + 1];
                    if (!isValid(nx, ny))
                        continue;
                    if (nx == cur.bx && ny == cur.by)
                        continue;
                    if (nx == tx && ny == ty)
                        return true;
                    if (seen[ny * m + nx]++)
                        continue;
                    q.push(ny * m + nx);
                }
            }
            return false;
        };

        auto canPush = [&](const Node &cur, int dx, int dy, Node *nxt) {
            nxt->bx = cur.bx + dx;
            nxt->by = cur.by + dy;
            nxt->px = cur.bx;
            nxt->py = cur.by;
            nxt->g = cur.g + 1;
            nxt->h = abs(nxt->bx - end.bx) + abs(nxt->by - end.by); // distance to target
            if (!isValid(nxt->bx, nxt->by))
                return false;
            return hasPath(cur, cur.bx - dx, cur.by - dy);
        };

        vector<int> seen(m * n * 4);
        priority_queue<Node> q;
        start.g = 0;
        start.h = abs(start.bx - end.bx) + abs(start.by - end.by);
        q.push(start);

        while (q.size()) {
            Node cur = q.top();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                Node nxt;
                if (!canPush(cur, dirs[i], dirs[i + 1], &nxt) || seen[nxt.key()]++)
                    continue;
                if (nxt.bx == end.bx && nxt.by == end.by)
                    return nxt.g;
                q.push(nxt);
            }
        }
        return -1;
    }
};
int main() {
    vector<vector<char>> grid = {{'#', '#', '#', '#', '#', '#'}, {'#', 'T', '#', '#', '#', '#'},
                                 {'#', '.', '.', 'B', '.', '#'}, {'#', '.', '#', '#', '.', '#'},
                                 {'#', '.', '.', '.', 'S', '#'}, {'#', '#', '#', '#', '#', '#'}}; // 3

    grid = {{'#', '#', '#', '#', '#', '#'}, {'#', 'T', '#', '#', '#', '#'},
            {'#', '.', '.', 'B', '.', '#'}, {'#', '#', '#', '#', '.', '#'},
            {'#', '.', '.', '.', 'S', '#'}, {'#', '#', '#', '#', '#', '#'}}; // -1
    grid = {{'#', '#', '#', '#', '#', '#'}, {'#', 'T', '.', '.', '#', '#'},
            {'#', '.', '#', 'B', '.', '#'}, {'#', '.', '.', '.', '.', '#'},
            {'#', '.', '.', '.', 'S', '#'}, {'#', '#', '#', '#', '#', '#'}}; // 5
    grid = {{'#', '#', '#', '#', '#', '#', '#'},
            {'#', 'S', '#', '.', 'B', 'T', '#'},
            {'#', '#', '#', '#', '#', '#', '#'}}; // -1

    grid = {{'#', '.', '.', '#', 'T', '#', '#', '#', '#'},
            {'#', '.', '.', '#', '.', '#', '.', '.', '#'},
            {'#', '.', '.', '#', '.', '#', 'B', '.', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '.', '.', '.', '#', '.', 'S', '#'},
            {'#', '.', '.', '#', '.', '#', '#', '#', '#'}}; // 8
    grid = {{'#', '#', '.', '#', '.', '.', '.', '.'},
            {'.', '.', '.', '.', '.', '.', '.', '.'},
            {'.', '.', '.', '.', '.', 'T', '.', '#'},
            {'.', '.', '.', '.', '.', '#', '.', '.'},
            {'.', '.', '.', '.', '.', '#', '.', '.'},
            {'.', '.', '.', '.', '.', '.', 'S', '.'},
            {'.', '.', '.', 'B', '.', '.', '.', '.'},
            {'.', '.', '.', '.', '.', '.', '.', '.'}};

    Solution s;
    cout << s.minPushBox(grid) << endl;

	return 0;
}
