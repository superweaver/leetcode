#include "common.h"
class Solution {
public:
    string longestPrefix(string s) {
        // s.length is limited
        // a hash method
        long left = 0, right = 0,  mul = 1, mod = 1000000007;
        int length = 0;
        for(int i = 0, j = s.size() - 1; i < s.size() - 1; ++i, --j)
        {
            int cl = s[i] - 'a', cr = s[j] - 'a';
            left = (left * 26 + cl) % mod;

            // mul is only used for right
            // cr need to multipty this mul before adding previous right
            right = (right + mul * cr) % mod;
            // update mul
			mul = (mul * 26) % mod;

            // set or update new length
			if(left == right)
			{
				length = i + 1;
			}
		}
        return s.substr(0, length);
    }

    string longestPrefix_kmp(string s) {
        // https://www.youtube.com/watch?v=dgPabAsTFa8
        // https://www.youtube.com/watch?v=3IFxpozBs2I
        //
        // KMP
		// this is to calculate the longest common prefix/suffix for s itself
        int n = s.size();
        vector<int> prefix_len(n, 0);
        // prefix_len[0] = 0;
        int len = 0;

        int i = 1;
		while(i < n)
		{
			if(s[len] == s[i])
			{
				prefix_len[i++] = ++len;
			}
			else
			{
				if (len > 0) {
                    len = prefix_len[len - 1];
                } else {
                    prefix_len[i++] = len; // len = 0;
                }
			}
		}
        //return s.substr(0, prefix_len[n-1]);
        s.resize(prefix_len[n-1]);
        return s;
	}
};

int main() {
    string text = "level"; // "l"
    text = "ababab";   // abab
    text = "leetcodeleet"; // leet
//    text = "a"; // ""
	Solution s;
    cout << s.longestPrefix(text) << endl;

	return 0;
}
