#include "common.h"
class Solution {
public:
    // not solved
    int numberWays(vector<vector<int>>& hats) {
        // https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/discuss/608686/C%2B%2B-Bit-masks-and-Bottom-Up-DP
        //
		// n: number of persons, 10 at most
		// h: number of hats, 40 at most
		// Time Complexity: O(2^n * h)
		// Space Complexity: O(2^n)
		// from the complexity analysis, you can also see why re-organization is critical in passing OJ
		
        vector<vector<int>> persons(40);
        const int n(hats.size()), mod(1e9 + 7);
		
		// masks range from 00...0 to 11...1 (n-digit binary number)
		// i-th digit represents whether i-th person has already had a hat
		// Base case: no one has a hat at first
        vector<int> masks(1 << n);
		masks[0] = 1; // number of ways

		// re-organize, hats -> persons
		// persons[i] means hat i can be used by these people
		for (int i = 0; i < n; ++i) {
            for (const int& h: hats[i]) {
                persons[h - 1].emplace_back(i); 
            }
        }

		for(int i = 0; i < 40; ++i)         // hats
		{ 
			// note : order
			for(int j = (1 << n) - 1; j >= 0; --j)  // masks
			{ 
				for(const int& p : persons[i])      // persons
				{ 
					// if the current state j implies that p-th person hasn't had a hat yet
					// we can give the i-th hat to that person, and update the state
					if((j & (1 << p)) == 0)
					{
                        // j | (1 << p) is new state
                        // j is current state
						masks[j | (1 << p)] += masks[j];
						masks[j | (1 << p)] %= mod;
					}
				}
			}
		}

		// return the state that each person has a hat
        return masks[(1 << n) - 1];
    }


	int numberWays_bruteforce(vector<vector<int>>& hats) {
	    int n = hats.size();	
        for(auto &v : hats) {
            sort(v.begin(), v.end());
        }
		sort(hats.begin(), hats.end(), [](const vector<int>& v1, const vector<int>& v2) {
			if(v1.size() != v2.size())
			{
				return v1.size() < v2.size();
			}
			else
			{
				return v1 < v2;
			}
		});
        vector<long> prefers;
		for(auto& v : hats)
		{
            long prefer = 0L;
            for (auto h : v) {
                prefer |= (1L << (h-1));
            }
            prefers.push_back(prefer);
		}

		long used = 0L;
        result = 0;
        dfs(0, n, used, prefers);
		return result;
	}
private:
    long result;
    const int Mod = 1000000007;
	long mask = (1L << 40) - 1;
	void dfs(int start, int n,  long used, vector<long>& prefers) {
        if (start == n) {
            result +=1;
            result %= Mod;
            return ;
        }
		auto prefer = prefers[start];
		prefer &= ~used;
        prefer &= mask;
		while(prefer)
		{
			long lowerbit = prefer & -prefer;
			dfs(start + 1, n, used | lowerbit, prefers);
			prefer -= lowerbit;
		}
	}
};

int main() {
    vector<vector<int>> hats = {{1,2,3},{2,3,5,6},{1,3,7,9},{1,8,9},{2,5,7}}; // 111
    //hats = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}}; // 24
    //hats = {{3,5,1},{3,5}}; // 4



	Solution s;
    cout << s.numberWays(hats) << endl;

	return 0;
}
