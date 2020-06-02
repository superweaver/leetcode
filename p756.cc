#include "common.h"
class Solution {
  public:
    bool pyramidTransition(string bottom, vector<string> &allowed) {
        // brutal
        int n = bottom.size();
        if (n == 1) {
            return true;
        }
        unordered_map<int, vector<int>> cache;
        for (auto &s : allowed) {
            cache[(((int)s[0]) << 8) + s[1]].push_back(s[2]);
        }
        if (cache.empty()) {
            return false;
        }
        vector<unordered_set<int>> layer(n);
        for (int i = 0; i < n; ++i) {
            layer[i].insert(bottom[i]);
        }
        return reachtop(cache, layer, n);
    }

  private:
    bool reachtop(const unordered_map<int, vector<int>> &cache, vector<unordered_set<int>> &layer,
                  int n) {
        if (n == 1) {
            return true;
        }
        // layer[i] contains all candidates for that slot
        vector<unordered_set<int>> nextlayer(n - 1);
        for (int i = 1; i < n; ++i) {
            auto &pre = layer[i - 1];
            auto &cur = layer[i];
            for (auto j : pre) {
                for (auto k : cur) {
                    int key = (j << 8) + k;
                    if (cache.count(key)) {
                        auto &v = cache.at(key);
                        nextlayer[i - 1].insert(v.begin(), v.end());
                    }
                }
            }
            if (nextlayer[i - 1].empty()) {
                return false;
            }
        }
        return reachtop(cache, nextlayer, n - 1);
    }
};

int main() {

    Solution s;

    return 0;
}
