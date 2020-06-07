#include "common.h"
class Solution {
  public:
    int snakesAndLadders(vector<vector<int>> &board) {
        int n = board.size();
        // n >= 2;
        // n <= 20;
        int N = n * n;
        vector<bool> visited(N + 1, false);
        unordered_map<int, pair<int, int>> i2c;
        for (int i = 1; i <= N; ++i) {
            i2c[i] = toRowColumn(i, n);
        }
        int moves = 0;
        queue<int> q;
        q.push(1);
        visited[1] = true;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int current = q.front();
                // cout << current << " ";
                if (current == N) {
                    return moves;
                }
                q.pop();
                for (int i = current + 1; i <= current + 6; ++i) {
                    if (i <= N) {
                        if (!visited[i]) {
                            visited[i] = true;
                            auto p = i2c[i];
                            int v = board[p.first][p.second];
                            if (v > 0) {
                                // if (!visited[v]) {
                                //		visited[v] = true;
                                // just move but no visit
                                q.push(v);
                                //	}
                            } else {
                                q.push(i);
                            }
                        }
                    } else {
                        break;
                    }
                }
            }
            moves++;
            // cout << endl;
        }
        return -1;
    }

  private:
    pair<int, int> toRowColumn(int i, int n) {
        // i is 1-indexed
        i--;
        int r = i / n;
        int c = i % n;
        if (r & 1) {
            c = n - 1 - c;
        }
        r = n - 1 - r;
        return {r, c};
    }
};

int main() {

	Solution s;

	return 0;
}
