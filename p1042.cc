#include "common.h"
// https : // blog.csdn.net/fuxuemingzhu/article/details/91357466
// four color
class Solution {
	public:
		vector<int> gardenNoAdj(int N, vector<vector<int>> &paths) {
			// prepare graph
			vector<vector<int>> graph(N);
			for (auto &v : paths) {
				graph[v[0] - 1].push_back(v[1] - 1);
				graph[v[1] - 1].push_back(v[0] - 1);
			}
			vector<int> color(N, 1); // note color is 1, 2, 3, 4
			for (int i = 0; i < N; ++i) {
				int neighbor_color = 0; 
				for (auto n : graph[i]) {
					neighbor_color |= (1 << (color[n])); // use bit 1 2, 3, 4
				}
				for (int c = 1; c < 5; ++c) {
					if (!(neighbor_color & (1 << c))) { // this color is not used, use this color
						color[i] = c;
						break;
					}
				}

			}
			return color;
        }
};

int main() {
    int N = 3; 
	vector<vector<int>> paths = {{1, 2}, {2, 3}, {3, 1}};
    Solution s;
	displayvector(s.gardenNoAdj(N, paths));
    return 0;
}
