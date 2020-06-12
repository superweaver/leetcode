#include "common.h"
class Solution {
  public:
    int minDominoRotations(vector<int> &A, vector<int> &B) {
        vector<int> equal;
        vector<int> top(7, 0);
        vector<int> bottom(7, 0);
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            if (A[i] == B[i]) {
                if (equal.empty()) {
                    equal.push_back(i);
                } else {
                    if (A[equal.back()] != A[i]) {
                        return -1;
                    } else {
                        equal.push_back(i);
                    }
                }
            } else {
                top[A[i]]++;
                bottom[B[i]]++;
                if (!equal.empty()) {
                    if (A[i] != A[equal.back()] && B[i] != A[equal.back()]) {
                        return -1;
                    }
                }
            }
        }
        if (equal.empty()) {
            for (int i = 1; i < 7; ++i) {
                if (top[i] + bottom[i] == n) {
                    return min(top[i], bottom[i]);
                }
            }
            return -1;
        } else {
            int v = A[equal.back()];
            if (top[v] + bottom[v] + equal.size() == n) {
                return min(top[v], bottom[v]);
            } else {
                return -1;
            }
        }
    }
};

int main() {

	Solution s;

	return 0;
}
