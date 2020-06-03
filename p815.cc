#include "common.h"
class Solution {
  public:
    int numBusesToDestination(vector<vector<int>> &routes, int S, int T) {
        // stop : route
        if (S == T) {
            return 0; // stupid
        }
        unordered_map<int, unordered_set<int>>
            stop2route; // stop -> routes who have stop at this stop
        int n = routes.size();
        for (int i = 0; i < n; ++i) {
            auto &v = routes[i];
            for (auto r : v) {
                stop2route[r].insert(i);
            }
        }

        // bfs
        unordered_set<int> visited_routes; // routes
        queue<int> q;
        unordered_set<int> current_layer; // stops
        int bus = 1;
        auto &rs = stop2route[S];
        for (auto i : rs) {
            current_layer.insert(routes[i].begin(), routes[i].end());
            visited_routes.insert(i);
        }
        if (current_layer.count(T)) {
            return bus;
        }
        for (auto stop : current_layer) {
            q.push(stop);
        }

        while (!q.empty()) {
            int node = q.size();
            unordered_set<int> nextlayer;
            while (node--) {
                int stop = q.front();
                q.pop();
                auto &rs = stop2route[stop];
                for (auto i : rs) {
                    if (!visited_routes.count(i)) {
                        if (stop2route[T].count(i)) {
                            return bus + 1;
                        }
                        visited_routes.insert(i);
                        nextlayer.insert(routes[i].begin(), routes[i].end());
                    }
                }
            }
            // !!!
            for (auto i : current_layer) {
                nextlayer.erase(i);
            }
            current_layer.swap(nextlayer);
            for (auto stop : current_layer) {
                q.push(stop);
            }
            bus++;
        }
        return -1;
    }
};

int main() {

    Solution s;

    return 0;
}
