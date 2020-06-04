#include "common.h"
class UF {
  public:
    UF(int n) {
        if (n > 0) {
            parents = vector<int>(n, 0);
            for (int i = 0; i < n; ++i) {
                parents[i] = i;
            }
            size = vector<int>(n, 1);
            count = n;
        } else {
            count = 0;
        }
    }

    bool isSameGroup(int u, int v) { return find(u) == find(v); }
    void Union(int u, int v) {
        if (isSameGroup(u, v)) {
            return;
        }
        int uid = find(u);
        int vid = find(v);
        int &usize = size[uid];
        int &vsize = size[vid];
        if (usize < vsize) {
            vsize += usize;
            parents[uid] = vid;
        } else {
            usize += vsize;
            parents[vid] = uid;
        }
        count--;
    }
    int getCount() { return count; }

  private:
    int find(int node) {
        while (node != parents[node]) {
            parents[node] = parents[parents[node]];
            node = parents[node];
        }
        return node;
    }
    int count; // count of groups
    vector<int> parents;
    vector<int> size;
};
class Solution {
  public:
    int carFleet(int target, vector<int> &position, vector<int> &speed) {
        vector<pair<int, int>> pi; // position and index
        int n = position.size();
        for (int i = 0; i < n; ++i) {
            pi.push_back({position[i], i});
        }
        sort(pi.begin(), pi.end());
        UF uf(n);
        for (int j = n - 1; j >= 0;) {
            int pos_j = pi[j].first;
            int index_j = pi[j].second;
            int i = j - 1;
            for (; i >= 0; --i) {
                int pos_i = pi[i].first;
                int index_i = pi[i].second;
                // overflow
                // another way is to use double and division
                if ((long long)(target - pos_i) * speed[index_j] <=
                    (long long)(target - pos_j) * speed[index_i]) {
                    uf.Union(j, i);
                } else {
                    break;
                }
            }
            j = i;
        }
        return uf.getCount();
    }
};

int main() {

    Solution s;

    return 0;
}
