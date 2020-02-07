#include "common.h"
class Solution {
public:
    int numSquarefulPerms(vector<int>& A) {
		// 1 <= A.length <= 12
		// 0 <= A[i] <= 1e9
		sort(A.begin(), A.end());
		int n = A.size();
		unordered_map<int, set<int>> cache;
		for (int i = 0;	i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j)  {
					continue;
				}
				int sum = A[i] + A[j];
				int t = sqrt(sum);
				if (t * t == sum) {
					cache[i].insert(j);
					cache[j].insert(i);
				}
			}
		}
		int result = 0;
		int pre = -1;
		int finalstate = (1 << n) - 1;
		for (int i = 0; i < n; ++i) {
			if (A[i] != pre) {
				int state = 1 << i;
				result += dfs(finalstate, state, i, A, cache);
			}
			pre = A[i];
		}
		return result;
    }
private:
	int dfs(int finalstate, int state, int index, const vector<int>& A, unordered_map<int, set<int>>& cache) {
		set<int>&v = cache[index];
		if (state == finalstate) {
			return 1;
		}
		int paths = 0;
		int pre = -1;
		for (auto n : v) {
			// A[n] is the value
			if (state & (1 << n)) continue;
			if (pre == A[n]) continue;
			paths += dfs(finalstate, state | (1 << n), n, A, cache);
			pre = A[n];
		}
		return paths;
	}
};

int main() {

	vector<int> A = {1, 17, 8};
	A = {2, 2, 2};
	A = {0, 4, 0, 4, 4, 0};
	Solution s;
	cout << s.numSquarefulPerms(A) << endl;

	return 0;
}
