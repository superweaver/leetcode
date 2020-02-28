#include "common.h"

class Solution {
public:
    vector<vector<int> > reconstructMatrix(int upper, int lower, vector<int>& colsum)
    {
        int sum = 0;
        for (auto c : colsum) {
            if (c & 1) {
                sum++;
            } else {
                // 0 or 2
                upper -= (c >> 1);
                lower -= (c >> 1);
            }
        }
        if (upper < 0 || lower < 0 || sum != upper + lower) {
            return {};
        } else {
            vector<vector<int> > result(2, vector<int>(colsum.size(), 0));
            for (size_t i = 0; i < colsum.size(); ++i) {
                if (colsum[i] == 2) {
                    result[0][i] = result[1][i] = 1;
                } else if (colsum[i] == 1) {
                    if (upper) {
                        result[0][i] = 1;
                        upper--;
                    } else {
                        result[1][i] = 1;
                        lower--;
                    }
                }
            }
            return result;
        }
    }
};

int main() {

    int upper = 5, lower = 5;
    vector<int> colsum = { 2, 1, 2, 0, 1, 0, 1, 2, 0, 1 };

    Solution s;
	auto r = s.reconstructMatrix(upper, lower, colsum);
	for(auto&v : r) {
		displayvector(v);
	}

    return 0;
}
