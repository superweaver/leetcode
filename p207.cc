#include "common.h"
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // topological sort
        vector<vector<int>> graph(numCourses); // from -> to
        for(auto& v: prerequisites) {
            graph[v[1]].push_back(v[0]);
        }
        vector<int> visited(numCourses, 0); // 0: not done, 1 : being searched, 2 : visited
        for (int i = 0; i < numCourses; ++i) {
            if (visited[i] == 0) {
                if (!dfs(visited, i, graph)) {
                    return false;
                }
            }
        }
        return true;
    }
private:
    bool dfs(vector<int>& visited, int index, vector<vector<int>>& graph) {
        if (visited[index] == 2) {
            return true;
        } else if (visited[index] == 1) {
            // there is a loop;
            return false;
        } else {
            // mark it as being visited 
            visited[index] = 1;
            for (auto next : graph[index]) {
                if (!dfs(visited, next, graph)) {
                    return false;
                }
            }
            // mark it visited
            visited[index] = 2;
            return true;
        }
    }
};

int main() {

    vector<vector<int>> prerequisites = {{1,0}};
    int numCourses = 2;
	Solution s;
    prerequisites = {{1,0},{0,1}};
    numCourses = 2;

    cout << s.canFinish(numCourses, prerequisites) << endl;

	return 0;
}
