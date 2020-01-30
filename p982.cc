#include "common.h"
class Solution {
public:
    int countTriplets(vector<int>& A) {
        int n = A.size();
        unordered_map<int, int> countTwo; // i < j
        unordered_map<int, int> countA;
        countA[A[0]]++;
        int r = (A[0] == 0);  // i = j = k
        for (int i = 1; i < n; ++i) {
            // i < j < k
            for (auto&p : countTwo) {
                if ((p.first & A[i]) == 0) {
                    r+= 6 * p.second;
                }
            }
            //i = j < k and  i < (j == k)
            for (auto&p : countA) {
                if ((p.first & A[i]) == 0) {
                    r += 6 * p.second; // 3 * p.second for i = j < k and 3 * p.second for i < j == k
                }
            }
            // i == j == k
            r += (A[i] == 0);
            countA[A[i]]++;
            for (int j = 0; j < i; ++j) {
                countTwo[A[j]&A[i]]++;
            }
        }
        return r;
    }
};
int main() {
    vector<int> A = {2, 1, 3};
	Solution s;
    cout << s.countTriplets(A) << endl;
	return 0;
}
