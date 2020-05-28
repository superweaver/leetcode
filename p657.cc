#include "common.h"
class Solution {
public:
    bool judgeCircle(string moves) {
        vector<int> counter(128, 0);
        for(char c : moves){
            counter[c]++;
        }
        // :)
        return (counter['U'] == counter['D']) && (counter['R'] == counter['L']);
    }

};

int main() {

	Solution s;

	return 0;
}
