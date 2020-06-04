#include "common.h"
class Solution {
  public:
    vector<int> advantageCount(vector<int> &A, vector<int> &B) {
        vector<pair<int, int>> p;
        int n = B.size();
        for (int i = 0; i < n; ++i) {
            p.push_back({B[i], i});
        }
        sort(p.begin(), p.end());
        sort(A.begin(), A.end());
        vector<bool> Avisited(n, false);
        // vector<bool> Bvisited(n, false);
        vector<int> result(n, -1);
        int start = 0;
        for (int i = 0; i < n; ++i) {
            int b = p[i].first;
            int j = upper(A, b, start, n);
            if (j >= 0) {
                result[p[i].second] = A[j];
                Avisited[j] = true;
                start = j + 1;
                //		Bvisited[p[i].second] = true;
            } else {
                break;
            }
        }
        int index = 0;
        for (int i = 0; i < n; ++i) {
            if (!Avisited[i]) {
                while (result[index] >= 0) {
                    index++;
                }
                result[index] = A[i];
            }
        }
        return result;
    }

  private:
    int upper(vector<int> &A, int v, int start, int n) {
        // return index of in A from start > v
        if (start < 0 || start >= n) {
            return -1;
        }
        if (A.back() <= v)
            return -1;
        int low = start;
        int high = n - 1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (A[mid] <= v) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }
};

int main() {

    Solution s;

    return 0;
}
