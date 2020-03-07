#include "common.h"
class Solution {
public:
    string tictactoe(vector<vector<int>>& moves) {
		vector<vector<int>> chess(N, vector<int>(N, -1));	
		for(size_t i = 0; i < moves.size(); ++i) {
			int r = moves[i][0];
			int c = moves[i][1];
            chess[r][c] = i & 1;
            int result = check(chess);
            if (result >= 0) {
                return result ? "B" : "A";
            }
        }
        if (moves.size() == T) {
            return "Draw";
        } else {
            return "Pending";
        }
    }
private:
	const size_t N = 3;
	const size_t T = N * N;
	int check(vector<vector<int>>& chess){
        // 0, or 1, some one win, 0->A, 1->B
		// -1 : no one win yet
		for (size_t i = 0; i < N; ++i) {
			auto &v = chess[i];
			if (v[0] >= 0 && v[0] == v[1] && v[1] == v[2]) {
				return v[0];
			}
		}
		for (size_t i = 0; i < N; ++i) {
            if (chess[0][i] >= 0 && chess[1][i] == chess[0][i] && chess[2][i] == chess[1][i]) {
				return chess[0][i];
            }
        }
		if (chess[0][0] >= 0 && chess[1][1] == chess[0][0] && chess[2][2] == chess[1][1]) {
			return chess[0][0];
		}

		if (chess[2][0] >= 0 && chess[1][1] == chess[2][0] && chess[0][2] == chess[1][1]) {
			return chess[1][1];
		}
        return -1;
	}
};

int main() {
    vector<vector<int>> moves = { { 0, 0 }, { 2, 0 }, { 1, 1 }, { 2, 1 }, { 2, 2 } }; // A
	moves = {{0,0},{1,1},{0,1},{0,2},{1,0},{2,0}}; //B
    moves = { { 0, 0 }, { 1, 1 }, { 2, 0 }, { 1, 0 }, { 1, 2 },
              { 2, 1 }, { 0, 1 }, { 0, 2 }, { 2, 2 } };  // draw

	moves = {{0,0},{1,1}};

    Solution s;
	cout << s.tictactoe(moves) << endl;

	return 0;
}
