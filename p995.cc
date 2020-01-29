#include "common.h"
class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        int n = A.size();
        int result = 0;
        int count = 0;
        A.push_back(1);
        // use A itself to record the delta of count
        for (int i = 0; i < n; ++i) {
            count += (A[i] >> 16);
            if ((count&1) == (A[i] & 0xFFFF)) {
                if (i + 1 > n) {
                    return -1;
                }
                int nextflip = 1- (A[i+1] >> 16);
                A[i+1] = (nextflip << 16)+ (A[i+1] &0xFFFF);

                if (i + K > n) {
                    return -1;
                }
                nextflip = 1- (A[i+K] >> 16);
                A[i+K] = (nextflip << 16)+ (A[i+K] &0xFFFF);
                result++;
            }
        }
        count += (A[n] >> 16);
        if (count&1) {
            return -1;
        }
        A.pop_back();
        return result;
    }
};

int main() {
    vector<int> A = {0,0,0,1,0,1,1,0};
    int K = 3;
 //   A = {1, 1, 0};
  //  K = 2;
//    A = {0, 1, 0};
 //   K = 1;
	Solution s;
    cout << s.minKBitFlips(A, K) << endl;

	return 0;
}
