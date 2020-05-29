#include "common.h"
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int> >& positions)
    {
        if (positions.empty()) {
            return {};
        }
        vector<int> result;
        vector<pair<int, int> > blocks;
        blocks.push_back({ INT_MIN, INT_MIN });
        blocks.push_back({ INT_MAX, INT_MAX });
        for (size_t i = 0; i < positions.size(); ++i) {
            vector<int>& square = positions[i];
            int start = square[0];
            int length = square[1];

            pair<int, int> leftedge(start, 0);  // height = 0;
            auto next_L = upper_bound(blocks.begin(), blocks.end(), leftedge);
            int i_next_L = 0 + distance(blocks.begin(), next_L);
            int i_pre_L = i_next_L - 1;

            pair<int, int> rightedge(start + length, 0);
            auto next_R = lower_bound(next_L, blocks.end(), rightedge);
            int i_next_R = i_next_L + distance(next_L, next_R);

            int beneath_h = 0;
            for (auto it = blocks[i_pre_L].second < 0 ? i_next_L : i_pre_L; it != i_next_R; ++it) {
                beneath_h = max(beneath_h, abs(blocks[it].second));
            }

            pair<int, int>* leftend = nullptr;
            if (blocks[i_pre_L].second > 0) {
                // split previous block
                leftend = new pair<int, int>(start, -blocks[i_pre_L].second);
            }
            pair<int, int>* rightend = nullptr;
            if (blocks[i_next_R].second < 0) {
                // generate a new rising edge (left edge)
                //
                rightend = new pair<int, int> (start + length, -blocks[i_next_R].second);
            }
            result.push_back(max(result.empty() ? 0 : result.back(), beneath_h + length));
            vector<pair<int, int> > right(next_R, blocks.end());
            blocks.resize(i_next_L);
            if (leftend) {
                blocks.push_back(*leftend);
                delete leftend;
            }
            // positive height to indicate left edge
            blocks.push_back({start, beneath_h + length});
            // negative height to indicate right edge
            blocks.push_back({start + length, -beneath_h - length});

            if (rightend) {
                blocks.push_back(*rightend);
                delete rightend;
            }

            blocks.insert(blocks.end(), right.begin(), right.end());
        }
        return result;
    }
};


int main() {

	Solution s;

	return 0;
}
