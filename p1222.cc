#include "common.h"
class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        vector<bool> q(64, false);
		for (auto&v : queens) {
            q[v[0] * 8 + v[1]] = true;
        }
        vector<pair<int, int>> operations{ { 0, 1 },   { 0, -1 }, { 1, 0 }, { -1, 0 },
                                           { -1, -1 }, { -1, 1 }, { 1, 1 }, { 1, -1 } };
		vector<vector<int>> result;
		for (auto&op : operations) {
			int row = king[0];
			int col = king[1];
			while(true) {
				row += op.first;
				col += op.second;
				if (row < 0 || row >= 8 || col < 0 || col >= 8){
					break;
				}
				if (q[row * 8 + col]) {
					result.push_back({row, col});
					break;
				}
			}
		}
		return result;
    }
};

int main() {

    vector<vector<int>> queens = { { 0, 1 }, { 1, 0 }, { 4, 0 }, { 0, 4 }, { 3, 3 }, { 2, 4 } };
    vector<int> king = { 0, 0 };
	queens = {{0,0},{1,1},{2,2},{3,4},{3,5},{4,4},{4,5}}, king = {3,3};
	queens = {{5,6},{7,7},{2,1},{0,7},{1,6},{5,1},{3,7},{0,3},{4,0},{1,2},{6,3},{5,0},{0,4},{2,2},{1,1},{6,4},{5,4},{0,0},{2,6},{4,5},{5,2},{1,4},{7,5},{2,3},{0,5},{4,2},{1,0},{2,7},{0,1},{4,6},{6,1},{0,6},{4,3},{1,7}}, king = {3,4};

    Solution s;
	auto r = s.queensAttacktheKing(queens, king);
	for (auto&v : r) {
		displayvector(v);
	}
    return 0;
}
