#include "common.h"
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();      // even
        vector<int> v2i(n, -1);  // this is the graph
        for (int i = 0; i < n; ++i) {
            v2i[row[i]] = i;
        }
        vector<int> groups = row;
        int result = 0;
        for (int i = 0; i < n; i += 2) {
            // if (groups[i] != -1) {  // not visited
            {
                if ((groups[i] / 2) != (groups[i + 1] / 2)) {
                    int next = groups[i];                                    // current one
                    int next_couple = (next & 1) ? (next - 1) : (next + 1);  // expected
                    int couple_loc = v2i[next_couple];
                    swap(groups[couple_loc], groups[i + 1]);
                    // must update location information
                    v2i[groups[i+1]] = i + 1;
                    v2i[groups[couple_loc]] = couple_loc;
                    result++;
                }
                // groups[i] = -1;
                // groups[i + 1] = -1;
            }
        }
        //displayvector(row);
        //displayvector(groups);
        return result;
    }
};


int main() {

	Solution s;

	return 0;
}
