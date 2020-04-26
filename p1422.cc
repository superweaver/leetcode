#include "common.h"
class Solution {
public:
    int maxScore(string s) {
        int n = s.size();
        int ones = 0;
        for (auto c : s) {
            ones += c - '0';
        }
        int result = INT_MIN;
        int zeros = 0;
		for(int i = 0; i < n - 1; ++i) // i is the end of left
		{
			if(s[i] - '0')
			{ // s[i] == '1'
				ones--;
			}
			else
			{ // s[i] == '0'
				zeros++;
			}
			result = max(result, zeros + ones);
		}
        return result;
	}
};

int main() {
    string str = "011101";
	str = "00111";
    str = "1111";
	Solution s;
    cout << s.maxScore(str) << endl;

	return 0;
}
