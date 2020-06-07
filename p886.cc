#include "common.h"
class Solution {
public:
	bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
		if (dislikes.empty()) {
			return true;
		}
		vector<vector<int>> dis(N + 1); // this is the graph
		for (auto&v : dislikes) {
			dis[v[0]].push_back(v[1]);
			dis[v[1]].push_back(v[0]);
		}
		vector<int> mark(N+1, 0);
		int flag = 1; // this is to flag or color each node
		for (int i = 0; i < N; ++i) {
            // if (dis[i].empty()) continue;
            // if (mark[i] != 0) continue;
			if ((!dis[i].empty()) && (mark[i] == 0)) {
				queue<int> q;
				q.push(i);
				mark[i] = flag;
				while (!q.empty()) {
					size_t size = q.size();
					flag = -flag; // for next layer, it should have another color/flag
					while (size--) {
						int current = q.front();
					//	cout << current << endl;
						q.pop();
						for (auto j : dis[current]) {
							if (mark[j] == 0) {
								mark[j] = flag;
								q.push(j);
							}
							else if (mark[j] == -flag) {
								return false;
							}
							//else {// do nothing}
						}
					}
				}
			}
		}
		return true;
	}
};

int main() {

	Solution s;

	return 0;
}
