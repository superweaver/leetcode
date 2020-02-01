#include "common.h"
class Solution {
public:
	// https://zxi.mytechroad.com/blog/graph/leetcode-952-largest-component-size-by-common-factor/
    int largestComponentSize(vector<int>& A) {
		//1 <= A.length <= 20000
		//1 <= A[i] <= 100000
		// Union-Find
		int n = *max_element(A.begin(), A.end());
		DJS uf(n + 1);
		for (auto a : A) {
			int bound = sqrt(a);
			for (int i = 2;  i <= bound; ++i) {
				if (a % i == 0) {
					uf.Union(i, a);
					uf.Union(i, a / i);
					// this is used to connect different common factor
					// note a / i is also >= i >= 2;
					// !!!!Union a with its factors
					// the factor with most child wins
					// return its number of children
				}
			}
		}
		unordered_map<int, int> count;
		int result = 1;
		for (auto a : A) {
			result = max(result, ++count[uf.Find(a)]);
		}
		return result;
	}
	struct DJS{
		DJS (int n) {
			max_size = 0;
			for (int i = 0; i < n; ++i) {
				parents.push_back(i);
			}
			sizes = vector<int>(n, 1);
		}
		int Find(int node) {
			while (node != parents[node]) {
				parents[node] = parents[parents[node]];
				node = parents[node];
			}
			return node;
		}
		void Union(int u, int v) {
			int uid = Find(u);
			int vid = Find(v);
			if (uid == vid) return;				
			int& usize = sizes[uid];
			int& vsize = sizes[vid];
			if (usize < vsize) {
				vsize += usize;
				parents[uid] = vid;
			} else {
				usize += vsize;
				parents[vid] = uid;
			}
		}
		private:
		int n ;
		vector<int> parents;
		vector<int> sizes;
		int max_size;
	};
};
int main() {

	vector<int> A = {20, 50, 9, 63};
	Solution s;
	cout <<	s.largestComponentSize(A) << endl;
	return 0;
}
