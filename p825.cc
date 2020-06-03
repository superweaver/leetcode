#include "common.h"
class Solution {
public:
    int numFriendRequests(vector<int>& ages)
    {
        // 1) A >= 100
        //      then A->B if A >= B > 0.5*A + 7
        // 2) A < 100
        //   then A->B if B <= 100, && A >= B > 0.5*A + 7
        //   then in all
        // A >= B > 0.5*A + 7
        // counting :(
        vector<int> all(121, 0);
        for(auto a:ages) {
            all[a]++;
        }
        int result = 0;
        int selfrequest = 0;
        for (auto A : ages) {
            // check how many Bs are there ?
            int start = (A) / 2 + 1 + 7;
            int end = A + 1; // exclusive
            if (end > start) {
                selfrequest++;
            }
            for(int i = start; i < end; ++i) {
                result += all[i];
            }
        }
        return result - selfrequest;
    }
};



int main() {

	Solution s;

	return 0;
}
