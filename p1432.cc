#include "common.h"
class Solution {
public:
	int maxDiff(int num)
	{
		vector<int> v;
		int n = num;
		while(n)
		{
			v.push_back(n % 10);
			n /= 10;
		}
		// get a
		int a = 0;
		int pre = -1; // point to the first non-9 element
		for(int i = v.size() - 1; i >= 0; --i)
		{
			if(pre >= 0)
			{
				if(v[i] == pre)
				{
					a = a * 10 + 9;
				}
				else
				{
					a = a * 10 + v[i];
				}
			}
			else
			{
				// pre not set yet
				if(v[i] != 9)
				{
					// set pre
					pre = v[i];
					a = a * 10 + 9;
				}
				else
				{
					a = a * 10 + 9;
				}
			}
		}

		int b = 0;
		if(v.back() != 1)
		{
            // set v.back to 1
			pre = v.back();
			for(int i = v.size() - 1; i >= 0; --i)
			{
				if(pre == v[i])
				{
					b = b * 10 + 1;
				}
				else
				{
					b = b * 10 + v[i];
				}
			}
		}
		else
		{
			// v.back() == 1, find first element that is not 1
			b = v.back();
			pre = -1;
			for(int i = v.size() - 2; i >= 0; --i)
			{
				if(pre >= 0)
				{
					if(v[i] == pre)
					{
						b = b * 10 + 0;
					}
					else
					{
						b = b * 10 + v[i];
					}
				}
				else
				{
					// not set yet
					//if(v[i] != 0 && v[i] != 1) // v.back() == 1
					if(v[i] > 1)
					{
						pre = v[i];
						b = b * 10 + 0;
					}
					else
					{
						b = b * 10 + v[i]; // v[i] = 0 or v[i] = 1
					}
				}
			}
		}
		return a - b;
	}
};

int main() {

    //vector <int> test = {555, 9, 123456, 10000, 9288,1101057 };
    vector <int> test = {1101057 };

	Solution s;
    for (auto t : test) {
		cout << t << " : " << s.maxDiff(t) << endl;
	}
	return 0;
}
