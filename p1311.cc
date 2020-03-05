#include "common.h"
class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos,
                                          vector<vector<int>>& friends, int id, int level)
    {
		int n = friends.size();
		vector<bool> visited(n, false);
		visited[id] = true;
		queue<int> q;
		q.push(id);
		int l = 0;
		while(!q.empty()) {
			int size = q.size();
			while(size--) {
				auto&f = friends[q.front()];
				q.pop();
				for(auto d : f) {
					if (!visited[d]) {
						q.push(d);
						visited[d] = true;
					}
				}
			}
			l++;
            if (l == level) {
				break;
            }
        }
		if (l != level) { // can't reach level
			return {};
		}
		unordered_map<string, int> count;
		while(!q.empty()) {
            auto& v = watchedVideos[q.front()];
			q.pop();
            for (auto&s : v) {
				count[s]++;
            }
        }
		vector<pair<int, string>> r;
		for (auto&p : count) {
			r.push_back({p.second, p.first});
		}
		sort(r.begin(), r.end());
		vector<string> result;
		for(auto&p : r) {
			result.push_back(p.second);
		}
		return result;
    }
};

int main() {
    vector<vector<string>> watchedVideos = { { "A", "B" }, { "C" }, { "B", "C" }, { "D" } };
    vector<vector<int>> friends = { { 1, 2 }, { 0, 3 }, { 0, 3 }, { 1, 2 } };
    int id = 0, level = 1;
	watchedVideos = {{"A","B"},{"C"},{"B","C"},{"D"}}, friends = {{1,2},{0,3},{0,3},{1,2}}, id = 0, level = 2;
	id = 1;
	level = 1;


    Solution s;
	displayvector(s.watchedVideosByFriends(watchedVideos, friends, id, level));

	return 0;
}
