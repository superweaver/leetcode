#include "common.h"
// https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/discuss/107159/C%2B%2B-DFS-recursion
/*
 * This question is very similar to searching for minimum value in the Binary Tree.
The only requirement is that this value must be different from the root value, k.

If the root value of a subtree == k,
         keep searching its children.
else,
         return the root value because it is the minimum of current subtree.

         */

class Solution {
  public:
    int findSecondMinimumValue(TreeNode *root) {
        // find first element > root->value
        if (!root) {
            return -1;
        }
        int ans = minval(root, root->val);
        return ans;
    }

  private:
    int minval(TreeNode *p, int first) {
        // p->val >= first;
        if (p == nullptr) {
            return -1;
        }
        if (p->val != first) { 
            return p->val;
        }
        // we are not clear which is smaller 
        int left = minval(p->left, first), right = minval(p->right, first);
        // if all nodes of a subtree = root->val,
        // there is no second minimum value, return -1
        if (left == -1)
            return right;
        if (right == -1)
            return left;
        return min(left, right);
    }
};

int main() {

	Solution s;

	return 0;
}
