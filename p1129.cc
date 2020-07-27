#include "common.h"
struct Queue{
	Queue(bool next) {
		nextisRed = next;
	}
	queue<int> q;
	bool nextisRed;
};

class Solution {
  public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &red_edges,
                                         vector<vector<int>> &blue_edges) {
        vector<int> result(n, INT_MAX);
        vector<vector<int>> r(n); // red graph
        for (auto &p : red_edges) {
            r[p[0]].push_back(p[1]);
        }
        vector<vector<int>> b(n); // blue graph
        for (auto &p : blue_edges) {
            b[p[0]].push_back(p[1]);
        }
        helper(true, n, result, r, b);
        helper(false, n, result, r, b);
        for (auto &i : result) {
            if (i == INT_MAX) {
                i = -1;
            }
        }
        return result;
    }

  private:
    void helper(bool next, int n, vector<int> &result, vector<vector<int>> &r,
                vector<vector<int>> b) {
        Queue q1(next); // start with red
        q1.q.push(0);
        vector<bool> visited1(n << 1, false);
        visited1[0 + next] = true;
        int step = 0;
        while (!q1.q.empty()) {
            size_t size = q1.q.size();
            while (size--) {
                auto c = q1.q.front();
                result[c] = min(result[c], step);
                q1.q.pop();
                int offset = (!q1.nextisRed) ? 0 : 1; // 0 -> red, 1->blue
                if (q1.nextisRed) {
                    for (auto &v : r[c]) {
                        int index = (v << 1) + offset;
                        if (!visited1[index]) {
                            visited1[index] = true;
                            q1.q.push(v);
                        }
                    }
                } else {
                    for (auto &v : b[c]) {
                        int index = (v << 1) + offset;
                        if (!visited1[index]) {
                            visited1[index] = true;
                            q1.q.push(v);
                        }
                    }
                }
            }
            q1.nextisRed = !q1.nextisRed;
            ++step;
        }
    }
};

int main() {
    int n = 3;
    vector<vector<int>> red_edges = { { 0, 1 }, { 0, 2 } }, blue_edges = { { 1, 0 } };

	n = 3, red_edges = {{0,1}}, blue_edges = {{1,2}};
	n = 3, red_edges = {{1,0}}, blue_edges = {{2,1}};
	n = 3, red_edges = {{0,1}}, blue_edges = {{2,1}};
	n = 3, red_edges = {{0,1},{1,2}}, blue_edges = {};
    n = 5;
    red_edges = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } };
    blue_edges = { { 1, 2 }, { 2, 3 }, { 3, 1 } };

    Solution s;
	displayvector(s.shortestAlternatingPaths(n, red_edges, blue_edges));
    return 0;
}
