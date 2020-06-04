#include "common.h"

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W)
    {
        if (hand.empty()) {
            return W == 0;
        }
        if (W == 1) {
            return true;
        }
        int n = hand.size();
        if (n % W != 0) {
            return false;
        }
        sort(hand.begin(), hand.end());

        queue<pair<int, int> > q;
        q.push({ hand[0], 0 });
        int i = 1;

        while(!q.empty() || i < n) {
            if(q.empty()) {
                q.push({hand[i++], 0 });
                continue;
            }
            if (i == n) {
                break;
            }
            auto current = q.front();
            if (current.first == hand[i]) {
                q.push({ hand[i++], 0 });
            } else {
                q.pop();
                // hand[i] > current.first
                if (hand[i] == current.first + 1) {
                    if (current.second + 1 <  W - 1) {
                        q.push({hand[i], current.second + 1});
                    }
                    // if (current.second + 1 == W - 1){ q.pop();}
                    i++;
                } else {
                    return false;
                }
           }
        }
        return (i == n) && q.empty();
    }
};


int main() {

	Solution s;

	return 0;
}
