#include "common.h"
class Solution {
public:
    // key : find the location where most vias meet
    int leastBricks(vector<vector<int>>& wall) {
        if (wall.empty()) {
            return 0;
        }
        int n = wall.size();
        int emptyLayer = 0;
        int i = 0;
        for (; i < n; ++i) {
            if (wall[i].empty()) {
                emptyLayer++;
            } else {
                break;
            }
        }
        if (emptyLayer == n) {
            return 0;
        }
        int Width = 0;
        vector<int>& layer = wall[i];
        for( auto w : layer) {
            Width += w;
        }
        unordered_map<int, int> via; // location : count
        for (; i < n; ++i) {
            vector<int>& layer = wall[i];
            if (layer.empty()) {
                emptyLayer++;
                continue;
            }
            int width = 0;
            for (auto w : layer) {
                width += w;
                via[width]++;
            }
        }
        via[Width] = 0;
        int maxVia = 0;
        for (auto p : via) {
            if (p.second > maxVia) {
                maxVia = p.second;
            }
        }
        return n - maxVia - emptyLayer;
    }
};

int main() {

	Solution s;

	return 0;
}
