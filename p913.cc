#include "common.h"
// game theory
//
class Solution {
    //https://www.cnblogs.com/grandyang/p/11515655.html
public:
	int catMouseGame(vector<vector<int>>& graph) {
		int n = graph.size();
        // at most 2*n
		vector<vector<vector<int>>> dp(2*n, vector<vector<int>>(n, vector<int>(n, -1)));
		// dp[step][mouse_node][cat_node] it means the solution to this problem if <step> has been used, cat is in <cat_node> and mouse is in <mouse_node>
		// need to get dp[0][1][2]
		// base case dp[?][0][?] = MOUSE_WIN
		// base case dp[?][x][x] = CAT_WIN
		// cat_node can't be 0
		return helper(graph, dp, 0, 1, 2, n);
	}
private:
	enum {DRAW, MOUSE_WIN, CAT_WIN};
	int helper(vector<vector<int>>& graph, vector<vector<vector<int>>>&dp, int step, int mouse_node, int cat_node, int n) {
		if (step >= 2 * n) {
			return DRAW; // no further movement can be achieved, it must be a DRAW
		}
		if (mouse_node == 0) {
			return dp[step][mouse_node][cat_node] = MOUSE_WIN;
		}
		if (mouse_node == cat_node) {
			return dp[step][mouse_node][cat_node] = CAT_WIN;
		}
		if (dp[step][mouse_node][cat_node] != -1) {
			return dp[step][mouse_node][cat_node];
		}
		bool mouse_turn = !(step & 1);
		if (mouse_turn) {
			bool must_be_cat_win = true;
			for (auto next_node : graph[mouse_node]) {
				int r = helper(graph, dp, step + 1, next_node, cat_node, n);
                if (r == MOUSE_WIN) { // by going this step, mouse can win, then go this step
                    return dp[step][mouse_node][cat_node] = r;
                } else {
                    if (r == DRAW) {
                        must_be_cat_win = false;
                    } // else { // if r = CAT_WIN, mouse won't take this node }
                }
            }
			if (must_be_cat_win) {
				return dp[step][mouse_node][cat_node] = CAT_WIN;
			}
			else {
				return dp[step][mouse_node][cat_node] = DRAW;
			}
		}
		else {// cat's turn
			bool must_be_mouse_win = true;
			for (auto next_node : graph[cat_node]) {
				if (next_node == 0) {
					continue;// cat can't go node zero
				}
				int r = helper(graph, dp, step + 1, mouse_node, next_node, n);
				if (r == CAT_WIN) {
					return dp[step][mouse_node][cat_node] = r;
				}
				else {
					if (r == DRAW) {
						must_be_mouse_win = false;
					}
				}
			}
			if (must_be_mouse_win) {

				return dp[step][mouse_node][cat_node] = MOUSE_WIN;
			}
			else {
				return dp[step][mouse_node][cat_node] = DRAW;
			}
		}
	}
};

int main() {

	Solution s;

	return 0;
}
