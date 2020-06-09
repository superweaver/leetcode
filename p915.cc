#include "common.h"

class Solution {
  public:
    int partitionDisjoint(vector<int> &A) {
        int st = 1, mx = A[0], all = A[0];
        // mx is existing max value of previous partition
        // all is max value up to index i
        const int n = A.size();
        for (int i = 1; i < n; ++i) {
            if (A[i] < mx) {
                // if A[i] < previous partion's max, then we need to extend partition to i + 1
                st = i + 1;
                mx = all; // update mx to be the max of new partition
            } else {
                // update new max for all
                all = max(all, A[i]);
            }
        }
        return st;
    };
};

class Solution1 {
  public:
    int partitionDisjoint(vector<int> &A) {
        vector<int> B(A);
        sort(B.begin(), B.end());
        int diff = 0;
        for (size_t i = 0; i < A.size(); ++i) {
            diff += (A[i] - B[i]);
            if (diff == 0) {
                return i + 1;
            }
        }
        return -1;
    }
};
class Solution2 {
  public:
    int partitionDisjoint(vector<int> &A) {
        int n = A.size();
        vector<int> leftMax(n, INT_MIN); // inclusive
        leftMax[0] = A[0];
        vector<int> rightMin(n, INT_MAX);
        // stop at i when rightMin[i] >= leftMax[i]
        // inclusive
        for (int i = 1; i < n; ++i) {
            if (A[i] > leftMax[i - 1]) {
                leftMax[i] = A[i];
            } else {
                leftMax[i] = leftMax[i - 1];
            }
        }
        // exclusive
        for (int j = n - 2; j >= 0; --j) {
            if (A[j + 1] < rightMin[j + 1]) {
                rightMin[j] = A[j + 1];
            } else {
                rightMin[j] = rightMin[j + 1];
            }
        }
        for (int i = 0; i < n; ++i) {
            if (leftMax[i] <= rightMin[i]) {
                return i + 1;
            }
        }
        return -1;
    }
};

int main() {

    vector<int> nums = {5, 0, 3, 8, 6};
    Solution s;
    cout << s.partitionDisjoint(nums) << endl;

    return 0;
}
