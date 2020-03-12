#include "common.h"
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
		// https://www.cnblogs.com/fish1996/p/11261100.html
		// not solved
		// |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
		// the max of this function should be taken from one of following form
		// 0) arr1[i] + arr2[i] + i - (arr1[j] + arr2[j] + j) 
		// 1) arr1[i] - arr2[i] + i - (arr1[j] - arr2[j] + j) 
		// 2) -arr1[i] + arr2[i] + i - (-arr1[j] + arr2[j] + j) 
		// 3) -arr1[i] - arr2[i] + i - (-arr1[j] - arr2[j] + j) 
		// Use the idea that abs(A) + abs(B) = max(A+B, A-B, -A+B, -A-B).

        int n = arr1.size();
        vector<int> v(4, 0);
        vector<int> minnum(4, INT_MAX);  // up to index i, the min value of four forms
        vector<int> maxnum(4, INT_MIN);  // up to index i, the max value of four forms
        int res = INT_MIN;
        //vector<int> signs{ 1, 1, -1, -1, 1 };
        for(int i = 0;i < n;i++)
        {

            v[0] = arr1[i] + arr2[i] + i;
            v[1] = arr1[i] - arr2[i] + i;
            v[2] = -arr1[i] + arr2[i] + i;
            v[3] = -arr1[i] - arr2[i] + i;
            
            for(int j = 0;j < 4;j++)
            {
                minnum[j] = min(minnum[j], v[j]);
                maxnum[j] = max(maxnum[j], v[j]);
				res = max(res, maxnum[j] - minnum[j]);
            }
        }
        return res;
    }
}; 

int main() {
    vector<int> arr1 = { 1, 2, 3, 4 }, arr2 = { -1, 4, 5, 6 };  // 13
    arr1 = { 1, -2, -5, 0, 10 }, arr2 = { 0, -2, -1, -7, -4 };  // 20

    Solution s;
	cout << s.maxAbsValExpr(arr1, arr2) << endl;

	return 0;
}
