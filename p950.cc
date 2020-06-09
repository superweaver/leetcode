#include "common.h"

class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        sort(deck.begin(), deck.end());
        queue<int> q; // store the index
        for(int i = 0; i < n; ++i) {
            q.push(i);
        }
        int index = 0; // index in sorted deck, pointing to element for next pick
        int put = 0;
        vector<int> result(n, 0);
        while (!q.empty()) {
            auto j = q.front();
            result[j] = deck[index++];
            q.pop();

            if(!q.empty()) {
                // pop
                auto k = q.front();
                q.pop();
                // put to bottom
                q.push(k);
            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
