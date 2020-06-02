#include "common.h"
typedef pair<int, pair<int, int>> Node;

struct NodeLess{
	bool operator() (const Node& a, const Node&b) {
		if (a.first != b.first) {
			return a.first > b.first;
		}
		else {
			return a.second > b.second;
		}
	}
};

class Solution {
public:
	int swimInWater(vector<vector<int>>& grid) {
		// priority_queue to store nodes passing by
		// bfs;
		int n = grid.size();
		N = n * n;
		priority_queue<Node, vector<Node>, NodeLess> q;
		int r = 0;
		int c = 0;
		grid[r][c] += N;
		q.push({ grid[r][c], { r, c } });
		while (!q.empty()) {
			Node current = q.top();
			q.pop();
			if (current.first >= N) {
				current.first -= N;
			}
			bool r = swim(n, grid, current.second.first, current.second.second, current.first, q);
			if (r) {
				return current.first;
			}
		}
		return INT_MAX;
	}
private:
	int N;
	vector<pair<int, int>> operations = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	bool swim(int n, vector<vector<int>>&grid, int row, int col, int height, priority_queue<Node, vector<Node>, NodeLess>& q) {
		if (row < 0 || row >= n || col < 0 || col >= n) {
			return false;
		}
		if (grid[row][col] < 0) {
			return false;
			/*
			if ((row == n - 1) && col == (n - 1)) {
				return true;
			}
			else {
				return false;
			}
			*/
		}//  can swim
		bool alreadyInQueue = (grid[row][col] >= N);
		int h = grid[row][col];
		if (alreadyInQueue) {
			h -= N; // acutal height
		}
		if (h >= 0 && h <= height) {
			grid[row][col] = -h - N; // reach here ;-N to avoid -0
			if ((row == n - 1) && col == (n - 1)) {
				return true;
			}
			for (size_t i = 0; i < operations.size(); ++i) {
				if (swim(n, grid, row + operations[i].first, col + operations[i].second, height, q)) {
					return true;
				}
			}
			return false;
		}
		else {

			// its height > current water level
			if (alreadyInQueue) {
				return false;
			}
			else {
				// add it in queue
				grid[row][col] += N;
				q.push({ grid[row][col], { row, col } });
				return false;
			}
		}
	}
};

int main() {

	Solution s;

	return 0;
}
