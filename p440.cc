#include "common.h"
//http://www.cnblogs.com/grandyang/p/6031787.html
//
class Solution {
public:
    int findKthNumber(int n, int k)
    {
        // view a number as a tree node with ten child node
        // eg: current = 1; then next = current + 1;
        // the child of current = 10 to 19
        int current = 1;  // the left of top layer
        k--;              // count of '1'
        while (k > 0) {
            // calculate the  number of child nodes of current
            // need to consider n !!!
            long left = current;
            long right = current + 1;
            long nodes = 0;
            while (left <= n) {
                nodes += (min(right, long(n + 1)) - left);  //  !!! n+1
                left *= 10;                                 // this may cause overflow
                right *= 10;
            }

            if (k >= nodes) {
                current++;
                k -= nodes; // this is all nodes root at current;
            } else {
                // !!! we can't use current as root
                // need to go one layer down
                --k;            // this is the count of current "current"
                current *= 10;  // go next layer
            }
        }
        return current;
    }
};

int main() {

	Solution s;

	return 0;
}
