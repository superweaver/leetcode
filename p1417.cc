#include "common.h"
class Solution {
public:
    string reformat(string s) {
		vector<int> count(128, 0);
        for(auto c : s) {
            count[c]++;
        }
        int c1 = 0;
        int c2 = 0;
        for (int i = 'a'; i <= 'z'; ++i) {
            c1 += count[i];
        }
        c2 = s.size() - c1;
		if(abs(c1 - c2) > 1)
		{
            return "";
		}
        string result;
		if(c1 >= c2)
		{
            // letter then number
            char i = 'a';
            char j = '0';
            while(true) {
				while(i <= 'z' && count[i] == 0)
				{
					++i;
				}
				if (i <='z' && count[i]) {
                    result.push_back(i);
                    count[i]--;
                } else {
                    break;
                }
                while(j<='9' && count[j] == 0) {
                    ++j;
                }
                if (j <= '9' && count[j]) {
                    result.push_back(j);
                    count[j]--;
                } else {
                    break;
                }
            }
		}
		else
		{
			// number then letter
			char i = 'a';
			char j = '0';
			while(true)
			{
				while(j <= '9' && count[j] == 0)
				{
					++j;
				}
				if(j <= '9' && count[j])
				{
					result.push_back(j);
					count[j]--;
				}
				else
				{
					break;
				}

				while(i <= 'z' && count[i] == 0)
				{
					++i;
				}
				if(i <= 'z' && count[i])
				{
					result.push_back(i);
					count[i]--;
				}
				else
				{
					break;
				}
			}
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
