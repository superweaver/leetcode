#include "common.h"
// The back tracking start from the back so that each search won't go too deep before it fails because smaller numbers have higher chance to be divisible among themselves. Also I don't use "visited" boolean array but use swap of an array of 1~N to avoid duplication.
class Solution {
  public:
    int countArrangement(int N) {
        vector<int> vs;
        for (int i = 0; i < N; ++i) {
            vs.push_back(i + 1); // any one can swap with 1
        }
        return counts(N, vs);
    }
    int counts(int n, vector<int> &vs) {
        if (n <= 0) {
            return 1;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (vs[i] % n == 0 || n % vs[i] == 0) {
                swap(vs[i], vs[n - 1]); // nice
                ans += counts(n - 1, vs);
                swap(vs[i], vs[n - 1]);
            }
        }
        return ans;
    }
};

class Solution_my {
public:
    int countArrangement(int N) {
        // 1 <= N <= 15
        if (N == 1) {
            return 1;
        }
        if (N == 2) {
            return 2;
        }
        vector<vector<int> > base(N, vector<int>());
        for (int i = 0; i < N; ++i) {
            int v = i + 1;
            for (int j = v; j <= N; ++j) {
                if (j % v == 0) {
                    base[v - 1].push_back(j);
                    if (j != v) { // !!! avoid repeating
                        base[j - 1].push_back(v);
                    }
                }
            }
        }

        int count = 0;
        vector<bool> visited(N, false);
        int start = 0;
        helper(start, N, base, visited, count);
        return count;
        //return 2 * count;
    }
    void helper(int start, int N, const vector<vector<int> >& base, vector<bool>& visited,
                int& count)
    {
        if (start >= N) {
            count++;
            return;
        }
        //int value = start + 1;
        const vector<int>& v = base[start];
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            int b = v[i];
            if (!visited[b - 1]) {
                visited[b-1] = true;
                helper(start + 1, N, base, visited, count);
                visited[b-1] = false;
           }
        }
    }
};

int main() {

    Solution s;
    for (int i = 1; i <= 15; ++i) {
        cout << i << " : " << s.countArrangement(i) << endl;
    }

    return 0;
}
