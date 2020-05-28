#include "common.h"
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        int result = INT_MIN;
        int r = helper(root, result);
        return (root)  ? result - 1 : 0;
    }
private:
  int helper(TreeNode *root, int &result) {
      // return the number of nodes of longest path of uni-value from root to leaf
      if (!root) {
          return 0;
      }
      int self = 1;
      int l = helper(root->left, result);
      int r = helper(root->right, result);
      if (!(root->left && root->left->val == root->val)) {
          l = 0;
      }
      if (!(root->right && root->right->val == root->val)) {
          r = 0;
      }
      int rv = max(r, l) + self;
      // return the number of nodes in the list that starts at root
      int nodes_passing_root = l + self + r; // include left and right
      result = max(result, nodes_passing_root);
      return rv;
  }
};


int main() {

	Solution s;

	return 0;
}
