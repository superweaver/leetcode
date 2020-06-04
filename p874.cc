#include "common.h"
class Solution {
public:
	int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
		int x = 0;
		int y = 0;
		enum {North, East, South, West, Dirs};
		int dir = North; // face dir
		unordered_map<int, vector<int>> rowmap;
		unordered_map<int, vector<int> > columnmap;
		for (auto&v : obstacles) {
			columnmap[v[0]].push_back(v[1]);
			rowmap[v[1]].push_back(v[0]);
		}
		for (auto&p : rowmap) {
			sort(p.second.begin(), p.second.end());
		}
		for (auto&p : columnmap) {
			sort(p.second.begin(), p.second.end());
		}

		int r = 0;
		for (auto c : commands) {
			if (c == -2) {
				dir = (dir + Dirs - 1) % Dirs;
			}
			else if (c == -1) {
				dir = (dir + 1) % Dirs;
			}
			else {
				if (dir & 1) {
					// East or West
					if (!rowmap.count(y)) {
						x += (dir == East) ? c : -c;
					}
					else {
						auto& s = rowmap[y];
						int nextx = x + ((dir == East) ? c : -c);
						if (dir == East){
							auto it = upper_bound(s.begin(), s.end(), x);
							if (it == s.end()) {
								x += c;
							}
							else {
								if (*it > nextx) {
									x += c;
								}
								else {
									x = (*it) - 1;
								}
							}
						}
						else {
							auto it = upper_bound(s.rbegin(), s.rend(), x, greater<int>());
							if (it == s.rend()) {
								x -= c;
							}
							else {
								if (*it < nextx) {
									x -= c;
								}
								else {
									x = (*it) + 1;
								}
							}

						}
					}
				}
				else {
					// North or South
					if (!columnmap.count(x)) {
						y += (dir == North) ? c : -c;
					}
					else {
						auto& s = columnmap[x];
						int nexty = y + ((dir == North) ? c : -c);
						if (dir == North) {
							auto it =  upper_bound(s.begin(), s.end(), y);
							if (it == s.end()) {
								y += c;
							}
							else {
								if (*it > nexty) {
									y += c;
								}
								else {
									y = (*it) - 1;
								}
							}
						}
						else {
							auto it = upper_bound(s.rbegin(), s.rend(), y, greater<int>());
							if (it == s.rend()) {
								y -= c;
							}
							else {
								if (*it < nexty) {
									y -= c;
								}
								else {
									y = (*it) + 1;
								}
							}
						}
					}
				}
				r = max(r, x*x + y * y);
			}
		}
		return r;
	}
};

int main() {

	Solution s;

	return 0;
}
