#include "common.h"
class Solution
{
public:

	int countVowelPermutation(int n)
	{
	/*
    Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
    Each vowel 'a' may only be followed by an 'e'.
    Each vowel 'e' may only be followed by an 'a' or an 'i'.
    Each vowel 'i' may not be followed by another 'i'.
    Each vowel 'o' may only be followed by an 'i' or a 'u'.
    Each vowel 'u' may only be followed by an 'a'.
    */
		//string vowels = "aeiou";
		constexpr int N = 5;
		constexpr int Mod = 1000000007;
        // from 
		vector<vector<int>> graph(N);
		graph[0].push_back(1); // a->e
		graph[1].push_back(0); // e->a
		graph[1].push_back(2); // e->i
		graph[2].assign({0, 1, 3, 4}); // i can't be followed by i
		graph[3].assign({2, 4}); // o->i, or u
		graph[4].push_back(0); // u->a

        // to is also OK
		// base case
		--n;
		vector<int> count(N, 1);
		vector<int> next(N, 0);

		// loop the result
		while(n--)
		{
			for(int i = 0; i < N; ++i)
			{
				for(auto j : graph[i])
				{
					next[j] += count[i];
					next[j] %= Mod;
				}
                count[i] = 0;

			}
			next.swap(count);
		}
		int r = 0;
		for(auto c : count)
		{
			r += c;
			r %= Mod;
		}
		return r;
	}
};

int main()
{

	Solution s;

	return 0;
}
