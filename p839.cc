#include "common.h"

class Solution {
  public:
    int numSimilarGroups(vector<string> &A) {
        int n = A.size();
        vector<int> parents(n, 0);
        vector<int> size(n, 1);
        for (int i = 0; i < n; ++i) {
            parents[i] = i;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int uid = find(i, parents);
                int vid = find(j, parents);
                if (uid == vid)
                    continue;
                if (check(A[i], A[j])) {
                    // union
                    int &usize = size[uid]; // reference :(
                    int &vsize = size[vid];
                    if (usize < vsize) {
                        vsize += usize;
                        parents[uid] = vid;
                    } else {
                        usize += vsize;
                        parents[vid] = uid;
                    }
                }
            }
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += (i == find(i, parents));
        }
        return result;
    }

  private:
    bool check(const string &a, const string &b) {
        int count = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                count++;
                if (count > 2) {
                    return false;
                }
            }
        }
        return true;
    }
    int find(int node, vector<int> &parents) {
        while (node != parents[node]) {
            parents[node] = parents[parents[node]];
            node = parents[node];
        }
        return node;
    }
};

int main() {

	Solution s;

	return 0;
}
