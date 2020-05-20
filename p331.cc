#include "common.h"
//https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/discuss/78566/Java-intuitive-22ms-solution-with-stack
//
//The capacity is the number of node that can be put in the tree. The initial value is 1, which means there can be a root.  When adding a node, capacity--; When adding a non-NULL node, it means we obtains two more leafs, then capacity +=2.  The final capacity should be equal to 0


class Solution {
  public:
    bool isValidSerialization(string preorder) {
        if (preorder.empty()) {
            return false;
        }
        preorder += ',';
        int sz = preorder.size(), idx = 0;
        int capacity = 1; // can be used to put root
        for (idx = 0; idx < sz; idx++) {
            if (preorder[idx] != ',') {
                continue;
            }
            // preorder[idx] == ','
            // and idx > 1
            capacity--; // one space is used by something before idx
            if (capacity < 0) {
                // invalid state
                return false;
            }
            if (preorder[idx - 1] != '#') { // previous node is digit
                capacity += 2;
            } // else {capacity += 0; // because preorder[idx-1] == '#', it can't create new space}
        }
        return capacity == 0;
    }
};
int main() {

	Solution s;

	return 0;
}
