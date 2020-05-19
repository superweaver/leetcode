#include "common.h"
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int> >& edges)
    {
        vector<int> result;
        if (edges.empty()) {
            for (int i = 0; i < n; ++i) {
                result.push_back(i);
            }
            return result;
        }
        unordered_map<int, vector<int> > Adjacent;
        vector<int> degrees(n, 0); // in + out degrees

        for (auto p : edges) {
            Adjacent[p.first].push_back(p.second);
            Adjacent[p.second].push_back(p.first);
            ++degrees[p.first];
            ++degrees[p.second];
        }
        vector<bool> visited(n, false);
        // bfs
        // start from leaves whose degrees == 1
        vector<int> currentlayer; // use vector instead of queue
        for (int i = 0; i < n; ++i) {
            if (degrees[i] == 1) {
                visited[i] = true;
                currentlayer.push_back(i);
            }
        }

        int minHeight = 0;
        while (true) {
            vector<int> nextlayer;
            for(size_t index = 0; index < currentlayer.size(); index++) {
                vector<int>& parents = Adjacent[currentlayer[index]];
                for (size_t i = 0; i < parents.size(); ++i) {
                    int parent = parents[i];
                    if (!visited[parent]) {
                        --degrees[parent];
                    }
                }
            }
            for (size_t index = 0; index < currentlayer.size(); index++) {
                vector<int>& parents = Adjacent[currentlayer[index]];
                for (size_t i = 0; i < parents.size(); ++i) {
                    int parent = parents[i];
                    if (!visited[parent] && degrees[parent] <= 1) {  // key point
                        visited[parent] = true;
                        nextlayer.push_back(parent);
                    }
                }

            }

            if (!nextlayer.empty()) {
                nextlayer.swap(currentlayer);
                minHeight++;
            } else {
                break;
            }
        }
        //cout << minHeight << endl;

        return currentlayer;
    }
};

int main() {

	Solution s;

	return 0;
}
