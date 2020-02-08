#include "common.h"
class Solution {
public:
    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
		unordered_set<long> L;
		unordered_map<int, int> row;
		unordered_map<int, int> column;
		unordered_map<int, int> sum;	 // lamps.first + lamps.second
		unordered_map<int, int> diff;	 // lamps.first - lamps.second
		for (auto &v : lamps) {
			int r = v[0];
			int c = v[1];
			row[r]++;
			column[c]++;
			sum[r + c]++;
			diff[r - c]++;
			L.insert(((long)r * N) + c);
		}
		vector<int> result;
		for (auto&q : queries) {
			int r = q[0];
			int c = q[1];
			int lit = 0;
			if (row[r] > 0 || column[c] > 0 || sum[r + c] > 0 || diff[r - c] > 0) {
				lit = 1;
			}
			result.push_back(lit);
			for (int i = r - 1; i <= r + 1; ++i) {
				if (i < 0 || i >= N) {
					continue;
				}
				for (int j = c - 1; j <= c + 1; ++j) {
					if (j < 0 || j >= N){
						continue;
					}
					long key = ((long)i * N) + j;
					if (L.count(key)) {
						L.erase(key);
						row[i]--;
						column[j]--;
						sum[i+j]--;
						diff[i-j]--;
					}
				}
			}
		}
		return result;
    }
};
int main() {

	Solution s;
	cout << sizeof(long) << endl;
	int	N = 5;
	vector <vector<int>> lamps = {{0,0},{4,4}}, queries = {{1,1},{1,0}};
	displayvector(s.gridIllumination(N, lamps, queries));

	return 0;
}
