#include "common.h"
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        unordered_map<int, int> mA;
        int n = A.size();
        int len = 0;
        for (int i = 0; i < n; ++i) {
            mA[A[i]] = i;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
              // A[i] A[j] ... A[x]¬
              // assume its length is len, then A[x]  > (len-2)*A[j]¬
              // why? len - 2 means excluse A[i] and A[x] 
              // among them A[j] is the minimum
              // so A[x] > (len-2) * A[j]
              //
                if ((len - 2) * (long long)A[j] > A.back()) {
                    break;
                }
                if (mA.count(A[j] - A[i]) && mA[A[j] - A[i]] < i) {
                    // processed;
                    continue;
                }

                pair<int, int> a = { A[i], i };
                pair<int, int> b = { A[j], j };
                int l = 2;
                while (mA.count(a.first + b.first) && mA[a.first + b.first] > b.second) {
                    l++;
                    swap(a, b);
                    b = {a.first + b.first, mA[a.first + b.first]};
                }
                len = max(len, l);
            }
       }
        return len >= 3 ? len : 0;
    }
};

int main() {

	Solution s;

	return 0;
}
