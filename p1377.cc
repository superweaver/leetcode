#include "common.h"
class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target)
    {

        vector<vector<int>> cache(n);
        vector<pair<int, double>> result(n, { -1, 0 });  // time, probability
        for (auto& v : edges) {
            cache[v[0] - 1].push_back(v[1] - 1);
            cache[v[1] - 1].push_back(v[0] - 1); // !!!  undirected tree
        }
        // 1 <= n <= 100
        // n is not large
        target--;                    // shift by one
        queue<pair<int, double>> q;  // node, p
		vector<int> visited(n, false);	
		visited[0] = true;
        q.push({ 0, 1 });
        int time = 0;
        result[0] = { time, 1 };
        while (!q.empty()) {
            size_t s = q.size();
            while (s--) {
                auto current = q.front();
                q.pop();
                int cnode = current.first;
                double cp = current.second;
				int next = 0;
                for (auto node : cache[cnode]) {
                    if (visited[node]) {
                        continue;
                    }
					next++;
                }
                if (!next) {
                    // no need to change p any more
                    if (cnode == target) {
                        return cp;
                    }
                } else {
                    double np = cp / next;
                    for (auto node : cache[cnode]) {
                        if (visited[node]) {
                            continue;
                        }
						visited[node] = true;
                        q.push({ node, np });
                        // update result
                        result[node] = { time + 1, np };
                    }
                    // remove
                    result[cnode] = { time, 0 };
                }
                // check target here
            }
            time++;
            if (time == t) {
                auto& p = result[target];
                return p.second;
            }
        }
        auto& p = result[target];
        return p.second;
    }
};

int main()
{
	int n = 7;
	vector<vector<int>> edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}};
	int t = 2, target = 4;

	n = 7, edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}}, t = 1, target = 7;
//	n = 7, edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}}, t = 20, target = 6;

//	n = 7, edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}}, t = 2, target = 3;
//	n = 8, edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}, {5, 8}}, t = 2, target = 8;
//	n = 3, edges = {{3, 2}, {2, 1}}, t = 1, target = 2;

    Solution s;
	cout << s.frogPosition(n, edges, t, target) << endl;
    return 0;
}
