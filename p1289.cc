#include "common.h"
// use a segment tree to find min of left part and right part
// -99 <= arr[i][j] <= 99
class SegmentTree {
  public:
    SegmentTree(const vector<int>& input) {
        n = input.size();
        arr.assign(2 * n, 0);
        for (int i = 0; i < n; ++i) {
            update(i, input[i]);
        }
    }
    int query (int i, int j) {
        // i is left index
        // j is right index
        int r = INT_MAX;
        i += n;
        j += n;
        // note: i <= j
        while (i <= j) {
             if (i&1) {
                 r = min(r, arr[i++]);
             }
             if (!(j&1)) {
                 r = min(r, arr[j--]);
             }
             i >>= 1;
             j >>= 1;
        }
        return r;
    }
    void update(int i, int v) {
        if (v != arr[i + n]) {
            add(i, v - arr[i + n]);
        }
    }
 private:
    vector<int> arr;
    int n;
    void add(int i, int delta) {
        i += n;
        arr[i] += delta;
        // update segment tree
        for (; i > 1; i >>= 1) {
            int pi = (i >> 1);
            arr[pi] = min(arr[pi << 1], arr[(pi << 1) + 1]);
        }
    }

 
};
class Solution {
  public:
    int minFallingPathSum(vector<vector<int>>& arr) {
        int n = arr.size();
        SegmentTree st(arr[0]);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int leftmin = INT_MAX;
                if (j - 1 >= 0) {
                    leftmin = st.query(0, j-1);
                }
                int rightmin = INT_MAX;
                if (n - j >= 2) {
                    rightmin = st.query(j+1, n-1);
                }
                arr[i][j] += min(leftmin, rightmin);
            }
            for (int j = 0; j < n; ++j) {
                st.update(j, arr[i][j]);
            }
        }
        return *min_element(arr[n - 1].begin(), arr[n - 1].end());
    }
};

int main() {
    vector<vector<int>> arr = {{1,2,3},{4,5,6},{7,8,9}};
    arr = {{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2},{2,2,1,2,2}};

	Solution s;
    cout << s.minFallingPathSum(arr) << endl;

	return 0;
}
