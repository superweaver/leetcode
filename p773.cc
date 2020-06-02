#include "common.h"

class Solution {
public:
	int slidingPuzzle(vector<vector<int>>& board) {
        // space can be reduced more
        //
		// 543210 // max key;
		const int n = 543210 + 1;
		const int target = 123450;
		bitset<n> flag;
		int value = getvalue(board);
		if (value == target) return 0;
		queue<vector<vector<int>>> q;
		flag.set(value, 1);
		q.push(board);
		int step = 0;
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				auto current = q.front();
				q.pop();
				int i = 0;
				int j = 0;
				bool found = false;
				for (i = 0;  i < 2; ++i) {
					for (j = 0; !found&&j < 3; ++j) {
						if (current[i][j] == 0) {
							found = true;
							break;
						}
					}
					if (found)break;
				}
				// left
				if (j > 0) {
					swap(current[i][j], current[i][j - 1]);
					int v = getvalue(current);
					if (v == target) { return step + 1; }
					if (!flag.test(v)) {
						flag.set(v, 1);
						q.push(current);
					}
					swap(current[i][j], current[i][j - 1]);
				}
				// right
				if (j < 2) {
					swap(current[i][j], current[i][j + 1]);
					int v = getvalue(current);
					if (v == target) { return step + 1; }
					if (!flag.test(v)) {
						flag.set(v, 1);
						q.push(current);
					}
					swap(current[i][j], current[i][j + 1]);
				}
				// top
				if (i == 0) {
					swap(current[i][j], current[i+1][j]);
					int v = getvalue(current);
					if (v == target) { return step + 1; }
					if (!flag.test(v)) {
						flag.set(v, 1);
						q.push(current);
					}
					swap(current[i][j], current[i+1][j]);

				}
				// bottom
				if (i == 1) {
					swap(current[i][j], current[i-1][j]);
					int v = getvalue(current);
					if (v == target) { return step + 1; }
					if (!flag.test(v)) {
						flag.set(v, 1);
						q.push(current);
					}
					swap(current[i][j], current[i-1][j]);
				}
			}
			step++;
		}
		return -1;
	}
 private:
	int getvalue(vector<vector<int>>&board) {
		int value = 0;
		for (size_t i = 0; i < board.size(); ++i) {
			for (size_t j = 0; j < board[i].size(); ++j) {
				value = 10 * value + board[i][j];
			}
		}
		return value;
	}
};

int main() {

	Solution s;

	return 0;
}
