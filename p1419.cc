#include "common.h"

class Solution {
public:
	int minNumberOfFrogs(string croakOfFrogs)
	{
		// croak
        // how many frogs are at these states?
		vector<int> counter(6, 0); // for [], ["c"], ["cr"], ["cro"], ["croa"],["croak"]
		vector<size_t> map(128);
		string base = "croak";
		for(size_t i = 0; i < base.size(); ++i)
		{
			map[base[i]] = i + 1;
		}

		int sum = 0; // how many frogs can appear at the same time
		int r = INT_MIN;
		for(auto c : croakOfFrogs)
		{
			size_t index = map[c];
			if(c == 'c')
			{
				counter[index]++;
				sum++;
			}
			else
			{
				if(counter[index - 1] == 0)
				{
					return -1;
				}
				else
				{
					counter[index - 1]--;
					counter[index]++;
				}
			}

			if(index == 5)
			{
				counter[index]--;
				sum--;
			}
			r = max(r, sum);
		}

        for(auto c : counter) {
            if (c) {
                return -1;
            }
        }
		return r;
	}
};

int main() {

    string croakOfFrogs = "croakcroak"; // 1
    croakOfFrogs = "crcoakroak"; // 2
    croakOfFrogs = "croakcrook"; // -1
    croakOfFrogs = "croakcroa"; // -1
	Solution s;
    cout << s.minNumberOfFrogs(croakOfFrogs) << endl;

	return 0;
}

