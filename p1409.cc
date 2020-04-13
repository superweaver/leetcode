#include "common.h"
class Solution {
   public:
    // Notice that the position of queries[i] in P is the result for queries[i]
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> pos2v(m, 0);
        vector<int> v2pos(m, 0);
        for (int i = 0; i < m; ++i) {
            pos2v[i] = i;
            v2pos[i] = i;
        }
        vector<int> result;
        for (auto q : queries) {
            --q;
            int pos = v2pos[q];
            result.push_back(pos);
            int v = q;
            for (; pos > 0; pos--) {
                pos2v[pos] = pos2v[pos - 1];
                v2pos[pos2v[pos]] = pos;
            }
            pos2v[0] = v;
            v2pos[v] = 0;
        }
        return result;
    }
};

int main() {
    vector<int> queries = {4, 1, 2, 2};
    int m = 4;                         // 3 1 2 0
    queries = {3, 1, 2, 1}, m = 5;     // 2 1 2 1
    queries = {7, 5, 5, 8, 3}, m = 8;  // 6 5 0 7 5

    Solution s;
    displayvector(s.processQueries(queries, m));
    return 0;
}
