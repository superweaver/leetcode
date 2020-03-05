#include "common.h"
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
		int n = arr.size();
		for (int i = 1; i < n; ++i) {
            arr[i] ^= arr[i - 1];
        }
		int len = queries.size();
		vector<int> result(len, 0);
		for(int i = 0; i < len; ++i) {
			auto&v = queries[i];
            int l = v[0] - 1;
            int left = (l >= 0) ? arr[l] : 0;
			int right = arr[v[1]];
            result[i] = left ^ right;
        }
		return result;
    }
};

int main()
{
    vector<int> arr = { 1, 3, 4, 8 };
    vector<vector<int>> queries = { { 0, 1 }, { 1, 2 }, { 0, 3 }, { 3, 3 } }; // 2, 7, 14, 8
	//arr = {4,8,2,10}, queries = {{2,3},{1,3},{0,0},{0,3}};

    Solution s;
	displayvector(s.xorQueries(arr, queries));
    return 0;
}
