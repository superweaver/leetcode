#include "common.h"
class Solution {
    // multiset: can keep same height
    // internally, it is BST and sorted.
  public:
    vector<pair<int, int>> getSkyline(vector<vector<int>> &buildings) {
        // store left rising edge as (left, -height)
        // and store the right falling edge as (right, height)
        // at the right falling edge, we need to remove its height from multiset
        // assume two left edge (l1,h1) , (l2, h2)
        // l1 == l2, h1 < h2;
        // since we sorted the pair, if we store positive h1 and h2
        // then (l1, h1) comes before (l2, h2) in edges, that is not what we want
        // we store left edge height as negative, to make l2,-h2 come before (l1, -h1);
        // after that, h2 will be the rbegin(), h1 will not show up

        vector<pair<int, int>> result;
        if (buildings.empty()) {
            return result;
        }
        vector<pair<int, int>> edges;
        for (auto b : buildings) {
            edges.push_back(make_pair(b[0], -b[2])); // critical
            edges.push_back(make_pair(b[1], b[2]));
        }
        sort(edges.begin(), edges.end()); // sort by x, and y

        multiset<int> height;             // critical
        height.insert(0);                 // this is critical;
        int preh = -1;
        for (auto e : edges) {
            if (e.second < 0) // left
            {
                height.insert(-e.second);
            } else { // right;
                // height.erase(e.second);
                height.erase(
                    height.find(e.second)); // !!!trap here, we can't use height.erase(e.second) (it
                                            // will erase all instaces);
            }
            int currenthighest =
                *height.rbegin(); // we need a 0 in multiset, otherwise, height will be empty;
            // only update if pre height is not same as current height
            if (currenthighest != preh) {
                result.push_back(make_pair(e.first, currenthighest));
                preh = currenthighest;
            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
