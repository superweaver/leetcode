#include "common.h"

class Solution {
public:
  int sumSubseqWidths_ref(vector<int> A) {
      /*
       * The order in initial arrays doesn't matter,
my first intuition is to sort the array.

For each number A[i]:

    There are i smaller numbers,
    so there are 2 ^ i sequences in which A[i] is maximum.
    we should do res += A[i] * (2 ^ i)

    There are n - i - 1 bigger numbers,
    so there are 2 ^ (n - i - 1) sequences in which A[i] is minimum.
    we should do res -= A[i] * (n - i - 1)

Done.
       * */
      sort(A.begin(), A.end());
      long c = 1, res = 0, mod = 1e9 + 7, n = A.size();
      for (int i = 0; i < n; ++i, c = c * 2 % mod)
          res = (res + A[i] * c - A[n - i - 1] * c) % mod;
      return (res + mod) % mod;
  }
    int sumSubseqWidths(vector<int>& A) {
		// happy! solved by myself
		// let A[i], A[j] be two elements in A or sorted A
		// how many sequencies will have to have these two as min and max?
		// 2^k , k is the number of elements in the sorted A from i +1 to j-1
		const int Mod = 1000000007;
		sort(A.begin(), A.end());
		int n = A.size();
		long long  r = 0;
		/*
		vector<int> cache(A.size() + 1, 1);
		for (size_t i = 1; i < cache.size(); ++i) {
			cache[i] = (((long long)(cache[i - 1])) << 1) % Mod;
		}
		*/

		//int count = 0;
		/*
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (A[j] == A[i]) continue;
				r += (A[j] - A[i])*(long long)(cache[j - i - 1]);
				r %= Mod;
				count++;
			}
		}
		*/

		/*
		for (int interval = 0; interval <= n - 2; ++interval) {
			for (int i = 0; i < interval + 1 && (n - 1 - i) >= (interval + 1); ++i) {
				// i , i + (interval+1), ..., i + k*(interval+1)
				int j = (n - 1 - i) / (interval + 1);
				j = i + j * (interval + 1);
				r += (A[j] - A[i])*(long long)cache[interval];
				r %= Mod;
				count++;
			}
		}
		*/
		//int left = 0;
		//int right = 0;
		int diff = 0; // == right - left;
		long long power2 = 1;
		for (int interval = 0; interval <= n - 2; ++interval) {
			// for certain interval k
			// r += (sum(last (k+1) terms in A) - sum(first(k+1) terms in A)) * cache[interval];
		//	left += A[interval];
		//	right += A[n - 1 - interval];
			//r += (right - left) * (long long)cache[interval];
			diff += A[n - 1 - interval] - A[interval];
			r = (r + diff * power2) % Mod;
			power2 = (power2 << 1) % Mod;
		}
		return (int)r;
	}
};

int main() {

	Solution s;

	return 0;
}
