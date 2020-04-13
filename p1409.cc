#include "common.h"
struct FenwickTreeOneBasedIndexing {
    // one-index implementation of Fenwick tree or BIT
    vector<int> bit; // binary indexed tree
    int n;

    FenwickTreeOneBasedIndexing(int n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    FenwickTreeOneBasedIndexing(vector<int> a)
        : FenwickTreeOneBasedIndexing(a.size()) {
        for (size_t i = 0; i < a.size(); i++) {
            add(i, a[i]);
        }
    }

    int sum(int idx) {
        // return the sum of A[0, idx] in original array A
        // g(i) = i - (i&-i);
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            ret += bit[idx];
        }
        return ret;
    }

    int sum(int l, int r) { 
        // return the sum of A[l, r] in original A
        return sum(r) - sum(l - 1);
    }

    // update A[idx] by a delta
    void add(int idx, int delta) {
        // h(i) = i + (i&-i);
        for (++idx; idx < n; idx += idx & -idx) {
            bit[idx] += delta;
        }
    }
};
class Solution {
  public:
    // Notice that the position of queries[i] in P is the result for queries[i]
    vector<int> processQueries(vector<int>& queries, int m) {
        //int n = (m << 1) + 1;
        int n = (m << 1);
        vector<int> pos(m + 1); // the pos of i in the fenwick tree's bit array;
        FenwickTreeOneBasedIndexing tree(n);
        for (int i = 1; i <= m; ++i) {
            pos[i] = i + m;      // initially 1 is in m + 1, ..., m is in 2*m
            tree.add(pos[i], 1); // 0 to 1
        }

        vector<int> result;
        for (auto q : queries) {
            result.push_back(tree.sum(pos[q] - 1));
            tree.add(pos[q], -1); // 1 to 0
            tree.add(pos[q] = m--, 1); // put to front of array; // 0 to 1
        }
        return result;
    }
};

class Solution_my {
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
    int m = 4;                        // 3 1 2 0
    queries = {3, 1, 2, 1}, m = 5;    // 2 1 2 1
    queries = {7, 5, 5, 8, 3}, m = 8; // 6 5 0 7 5

    Solution s;
    Solution_my s2;
    displayvector(s.processQueries(queries, m));
    displayvector(s2.processQueries(queries, m));
    return 0;
}
