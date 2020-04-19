#include "common.h"
class Solution {
public:
	int numberOfArrays(string s, int k)
	{
		// 1 <= s.length <= 10^5.
		// 1 <= k <= 10^9
		int n = s.size();
		// how many different ways you can get by using first i characters of s
		// can be reduced , at most 10 are needed;
		vector<int> dp(n + 1, 0);
		dp[0] = 1;
		if(s[0] == '0')
		{
			return 0;
		}
		constexpr int Mod = 1000000007;
        for (int i = 0; i <= n; ++i) {
            // dp[i] is known, use dp[i] to update later ones
            if (dp[i] == 0) {
                return 0;
            }
            if (s[i] == '0') { // s[i] is leading 0
                continue;
            }

            long temp = 0;
            // use s[i...]
			for(int j = i ; j < n; ++j)
			{
				temp = temp * 10 + s[j] - '0';
				if (temp > k) {
                    break;
                } else {
					dp[j + 1] = (dp[j + 1] + dp[i]) % Mod;
				}
			}
		}

        return dp.back();
	}

	int numberOfArrays2(string s, int k) {
        // 1 <= s.length <= 10^5.
        // 1 <= k <= 10^9
        int n = s.size();
        // can be reduced , at most 10 are needed;
        vector<int> dp(n + 1, 0); // how many different ways you can get by using first i characters of s
        dp[0] = 1;
        if (s[0] == '0') {
            return 0;
        }
        constexpr int Mod = 1000000007;
        vector<unsigned long> base; // 10^i
        base.push_back(1);
        for (int i = 1; i <= 9; ++i) {
            base.push_back(base.back() * 10);
        }
		for(int i = 0; i < n; ++i)
		{
			int j = i;
			unsigned long tmp = 0;
			while(j >= 0)
			{
				if(i - j >= (int)base.size())
				{
					if(!tmp)
					{
						// too many zero
						return 0;
					}
                    else {
						break;
                    }
				}
				tmp = tmp + (s[j] - '0') * base[i - j];
				if(tmp <= k)
				{
					if(tmp > 0 && s[j] != '0') // no leading zero
					{
						dp[i + 1] += dp[j];
						dp[i + 1] %= Mod;
					}
				}
				else
				{
					break;
				}
				--j;
			}

			if(!tmp && j == -1 )
			{
				//000000
				return 0;
			}
		}
        return dp.back();
	}
};

int main() {
    string s = "1000";
    int k = 1000; // 1
    s = "1000", k = 10; // 0
    s = "1317", k = 2000; // 8
    s = "2020", k = 30; // 1
    s = "1234567890", k = 90;
    s = "407780786171321121429620765476840275495357129574174233567552131453038760763182952432348422252546559691171161181440370120987634895458140447952079749439961325982629462531738374032416182281868731817661954890417245087359968833257550123324827240537957646002494771036413572415";
    k = 823924906;

//    s = "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
//    k = 1000000000;



	Solution so;

    cout << so.numberOfArrays2(s, k) << endl;
    cout << so.numberOfArrays(s, k) << endl;

	return 0;
}
