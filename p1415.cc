#include "common.h"
class Solution
{
public:
	string getHappyString(int n, int k)
	{
		//1 <= n <= 10
		//1 <= k <= 100
		int len = 1 << (n - 1);
		int total = 3 * len;
		if(k > total)
		{
			return ""; // no solution
		}
		string result;
		helper(n, n - 1, k, result);
		return result;
	}

private:
	void helper(size_t n, int index, int k, string& result)
	{
		while(result.size() < n)
		{
			// how may different strings do we have by using (index + 1) characters
			int block_size = 1 << index; // == 1 << index;
			int block_index = (k + block_size - 1) / block_size - 1; // 0 ,1, 2
			if(result.empty())
			{
				// block_index can be 0, 1, 2
				result.push_back(base[block_index]);
			}
			else
			{
				// block_index can be 0, 1
				result.push_back(base_nonempty[result.back() - 'a'][block_index + 1]);
			}

			k -= block_index * block_size;
			index--;
		}
	}

private:
	const vector<string> base_nonempty = {"abc", "bac", "cab"};
	const string base = "abc";
	// vector<int> next{1, 0, 0};
	// a->b
	// b->a
	// c->a
};

int main()
{
	int n = 3;
	int k = 9; // cab
	n = 3, k = 8; // bcb

	//	n = 10, k = 100; // abacbabacb
	Solution s;
	cout << s.getHappyString(n, k) << endl;

	return 0;
}
