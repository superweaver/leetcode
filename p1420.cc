#include "common.h"
class Solution {
public:

    int numOfArrays(int n, int m, int k) {
        if (k == 0) {
            return 0;
		}
		powers = vector<vector<long >>(m + 1, vector<long>(n + 1, 0)); // m^n
		for(int i = 1; i <= m; ++i)
		{
            powers[i][0] = 1;
		    long temp = 1;
			for(int j = 1; j <= n; ++j)
			{
				temp *= i;
				temp %= Mod;
				powers[i][j] = temp;
			}
		}

		vector<vector<vector<long>>> dp(m + 1,
										vector<vector<long>>(n + 1, vector<long>(k + 1, -1)));
		// the ways pick m elements out of k, total length is n
		// 1) don't use element m
		//      dp[m][n][k] += dp[m-1][n][k]
		// 2) pick k-1 out of m-1, using some elements len (len >= k-1), and followed by a "m",
		//    elements after first m are free to choose
		return helper(dp, m, n, k);
	}
   
private:
	long helper(vector<vector<vector<long>>>& dp, int m, int n,  int k)
	{
		// m >= k
        // n >= k
        
        if (m < 0 || n < 0 || k < 0) {
            return 0;
        }

		if(dp[m][n][k] >= 0) // has been computed
		{
			return dp[m][n][k];
		}

		if(!(m >= k && n >= k))
		{
			return dp[m][n][k] = 0;
		}
        // base case
        if (k == 1) {
            // no m
            dp[m][n][k] = helper(dp, m - 1, n, k);
			// use m as first element, then free to choose any element for remaining n-1 elements;
			return dp[m][n][k] = (dp[m][n][k] + powers[m][n - 1]) % Mod;
		}

		dp[m][n][k] = 0;
        // don't use m
		auto no_m = helper(dp, m - 1, n, k);
		dp[m][n][k] += no_m;
        
        // use m
        // pick k - 1 out m - 1 
        // change n
		for(int i = k - 1; i < n; ++i) // i is the new n
		{
			auto temp = helper(dp, m - 1, i, k - 1);
            // followed by one m ande then free choices
			auto freelength = n - (i + 1);
			dp[m][n][k] += temp * powers[m][freelength];
			dp[m][n][k] %= Mod;
		}

        cout << "m = " << m << ", n = " << n << ", k = " << k << ", v = " << dp[m][n][k] << endl;
		return dp[m][n][k] ;
	}

private:
	static constexpr long Mod = 1000000007;
	vector<vector<long >> powers; // m^n
};

int main() {

	int n = 2, m = 3, k = 1; // 6

	n = 20, m = 4, k = 1; //40690768

	//n = 49, m = 97, k = 1; // 866950271
    /*
	n = 9, m = 1, k = 1; // 1
	n = 5, m = 2, k = 3; //0
    */
    //n = 9, m = 7, k = 1;
	//n = 2, m = 1, k = 1;
	n = 50, m = 100, k = 25; // 34549172
	//n = 2, m = 4, k = 2; // 6
	n = 3, m = 4, k = 2; //  30
	n = 2, m = 3, k = 2; // 
	Solution s;
	cout << s.numOfArrays(n, m, k) << endl;

	return 0;
}
