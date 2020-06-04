#include "common.h"
class Solution {
public:
	vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
		int N = quiet.size();
		vector<vector<int> > cache(N); // graph
		for (auto&v : richer) {
            // v[0] > v[1]
			cache[v[1]].push_back(v[0]); // put all person richer than you as neighbor
		}
		vector<int> result(N, -1); // -1 is good
		for (int i = 0; i < N; ++i) {
			if (result[i] < 0) {
				dfs(i, result, quiet, cache);
			}
		}
		return result;
	}
private:
  int dfs(int start, vector<int> &result, const vector<int> &quiet,
          const vector<vector<int>> &cache) {
      if (result[start] >= 0) {
          // solved
          return result[start];
      }

      int r = start; // include himself
      for (auto p : cache[start]) {
          auto upper = dfs(p, result, quiet, cache); // return index;
          if (quiet[upper] < quiet[r]) {
              r = upper;
          }
      }
      return result[start] = r;
  }
};

int main() {

	Solution s;

	return 0;
}
