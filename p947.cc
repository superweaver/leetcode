#include "common.h"
class Solution {
    // https://zxi.mytechroad.com/blog/graph/leetcode-947-most-stones-removed-with-same-row-or-column/
    // https://www.jianshu.com/p/30d2058db7f7
  public:
    int removeStones(vector<vector<int>> &stones) {
        // connection : if point (i1, j1) shares same row or collumn with (i2, j2), then point (i1,
        // j2) is connected
        // !!! For any connected component, there is always a way to erase it back to one point
        // (shrink) so the final state is that there are x points in the 2D space, they don't share
        // same row or column; x = number of connected component so the most moves = stones.size() -
        // x
        //     1 <= stones.length <= 1000
        //     0 <= stones[i][j] < 10000
        const int N = 10000; // this can be reduced to max(max(r_i, c_i)) in stones
        DJS uf(2 * N);       // view row and column as
        for (auto &v : stones) {
            uf.Union(v[0], v[1] + N); // !!!!
        }
        unordered_set<int> roots;
        for (auto &v : stones) {
            roots.insert(uf.find(v[0]));
        }
        return stones.size() - roots.size();
    }

  private:
    struct DJS {
        DJS(int n) {
            parents.resize(n);
            for (int i = 0; i < n; ++i) {
                parents[i] = i;
            }
            sizes = vector<int>(n, 1);
        }
        void Union(int u, int v) {
            int uid = find(u);
            int vid = find(v);
            if (uid != vid) {
                int &usize = sizes[uid];
                int &vsize = sizes[vid];
                if (usize < vsize) {
                    vsize += usize;
                    parents[uid] = vid;
                } else {
                    usize += vsize;
                    parents[vid] = uid;
                }
            }
        }
        int find(int node) {
            while (node != parents[node]) {
                parents[node] = parents[parents[node]];
                node = parents[node];
            }
            return node;
        }

      private:
        vector<int> parents;
        vector<int> sizes;
    };
};

int main() {

	Solution s;

	return 0;
}
