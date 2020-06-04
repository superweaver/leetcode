#include "common.h"

class Solution {
  public:
    int shortestPathAllKeys(vector<string> &grid) {
        int m = grid.size();
        int n = grid[0].size();
        char K = 'a';
        int r = 0;
        int c = 0;
        const vector<int> dirs = {0, 1, 0, -1, 0};
        for (int i = 0; i < m; ++i) {
            auto &s = grid[i];
            for (int j = 0; j < n; ++j) {
                if (s[j] >= 'a' && s[j] <= 'z') {
                    K = max(K, s[j]);
                }
                if (s[j] == '@') {
                    r = i;
                    c = j;
                }
            }
        }
        K = K - 'a' + 1;
        int goal = (1 << K) - 1;
        int coordindate = r * n + c;
        int key = 0;
        int state = (coordindate << K) + key;
        int moves = 0;
        unordered_set<int> visited;
        visited.insert(state);
        queue<pair<int, int>> q;
        q.push({coordindate, key});
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto p = q.front();
                q.pop();
                if (p.second == goal) {
                    return moves;
                }
                r = p.first / n;
                c = p.first % n;
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dirs[i];
                    int nc = c + dirs[i + 1];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        char c = grid[nr][nc];
                        if (c == '.' || c == '@') {
                            coordindate = nr * n + nc;
                            key = p.second;
                            state = (coordindate << K) + key;
                            if (!visited.count(state)) {
                                visited.insert(state);
                                q.push({coordindate, key});
                            }
                        } else if (c >= 'a' && c <= 'z') {
                            coordindate = nr * n + nc;
                            key = (p.second | (1 << (c - 'a')));
                            state = (coordindate << K) + key;
                            if (!visited.count(state)) {
                                visited.insert(state);
                                q.push({coordindate, key});
                            }
                        } else if (c >= 'A' && c <= 'Z') {
                            coordindate = nr * n + nc;
                            bool haskey = p.second & (1 << (c - 'A'));
                            if (haskey) {
                                key = p.second;
                                state = (coordindate << K) + key;
                                if (!visited.count(state)) {
                                    visited.insert(state);
                                    q.push({coordindate, key});
                                }
                            }
                        }
                    }
                }
            }
            moves++;
        }
        return -1;
    }
};

int main() {

	Solution s;

	return 0;
}
