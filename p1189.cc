#include "common.h"
class Solution {
public:
    int maxNumberOfBalloons(string text) {
        // balloon
        vector<int> count(128, 0);
        for(auto c : text) {
            count[c]++;
        }
        int r = INT_MAX;
        r = min(count['b'], r);
        r = min(count['a'], r);
        r = min(count['l']/2, r);
        r = min(count['o']/2, r);
        r = min(count['n'], r);
        return r;
    }
};
