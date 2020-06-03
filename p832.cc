#include "common.h"
class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {

        int m = A.size();
        int n = A[0].size();
        for (int i = 0; i < m; ++i){
            auto &v = A[i];
            int j = 0;
            int k = n - 1;
            while(j < k){
                int temp = v[k];
                v[k--] = 1 - v[j];
                v[j++] = 1 - temp;
            }
            if (j == k){
                // invert is mandatory, while swap may not be needed
                v[j] = 1 - v[j];
            }
        }
        return A;
    }
};

int main() {

	Solution s;

	return 0;
}
