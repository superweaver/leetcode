#include "common.h"
class Solution {
public:

    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        dp = vector<vector<int>>(n, vector<int>(n, INT_MAX));
        M = vector<vector<int>>(n, vector<int>(n, -1));
		for (int i = 0; i < n; ++i) {
			dp[i][i] = 0;
			M[i][i] = arr[i];
		}

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
				int j = i + len - 1; // [i, j]
                int result = INT_MAX;
                int maxV = -1;
                for (int k = i; k + 1 <= j; ++k) {
					maxV = max(maxV, max(M[i][k], M[k+1][j]));
					result = min(result, dp[i][k] + dp[k+1][j] + M[i][k] * M[k+1][j]);
                }
				dp[i][j] = result;
				M[i][j] = maxV;
            }
        }
        return dp[0][n - 1];
    }
    int mctFromLeafValues_recursive(vector<int>& arr) {
		// divide array into two parts
		// get solution of left parts and max of left parts
		// get solution of right parts and max of rights
		// then final solution is solution of left + solution of right + max_left * max_right
		// pick the smallest one	
		int n = arr.size();
        dp = vector<vector<int> >(n , vector<int>(n, -1));
		M = vector<vector<int> >(n , vector<int>(n, -1));
        auto r = helper(arr, 0, n - 1);
		return r.first;
    }
private:
    vector<vector<int>> dp;
    vector<vector<int>> M;
	pair<int, int> helper(vector<int>& arr, int start, int end) {
		if (dp[start][end] >= 0) {
            return {dp[start][end], M[start][end]};
        }
		if (start == end) {
			dp[start][end] = 0;
			M[start][end] = arr[start];
            return {dp[start][end], M[start][end]};
		}
		/*
		if (end == start + 1) {
			dp[start][end] = arr[start] * arr[end];
			M[start][end] = max(arr[start], arr[end]);
            return {dp[start][end], M[start][end]};
		}
		*/
		int result = INT_MAX; 
		int maxV = -1;
		for (int i = start; i < end; ++i) { // i is left end
            auto left = helper(arr, start, i);
            auto right = helper(arr, i + 1, end);
			maxV = max(left.second, maxV);
			maxV = max(right.second, maxV);
			result = min(result, left.first + right.first + left.second * right.second);
        }
		dp[start][end] = result;
		M[start][end] = maxV;
        return { dp[start][end], M[start][end] };
	}
};


int main() {
	vector<int> arr = {6, 2, 4}; // 32
   // arr = { 10, 2, 15, 9, 1, 3, 8, 5, 13, 6, 11, 3, 8, 6, 5, 13, 13, 7 };
    Solution s;
	cout << s.mctFromLeafValues(arr) << endl;
	return 0;
}
