#include "common.h"
class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
		size_t total = 1 << n;
		vector<bool> visited(total, false);
		vector<int> result;
		result.push_back(start);
		visited[start] = true;
		while(result.size() != total) {
			int pre = result.back();
			for (int i = 0; i < n; ++i) {
				int probe = 1 << i;
                int candidate = (pre & probe) ? pre - probe : pre + probe;
				if (!visited[candidate]) {
					visited[candidate] = true;
					result.push_back(candidate);
					break;
				}
            }
		}
		return result;
    }
};

int main() {
	int n =	2, start = 3;
	n = 3, start = 2;
	Solution s;
	displayvector(s.circularPermutation(n, start));
	return 0;
}
