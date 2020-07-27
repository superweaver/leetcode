#include "common.h"
/*
 * Given a binary tree, return the values of its boundary in anti-clockwise direction starting from root. Boundary includes left boundary, leaves, and right boundary in order without duplicate nodes.

Left boundary is defined as the path from root to the left-most node. Right boundary is defined as the path from root to the right-most node. If the root doesn't have left subtree or right subtree, then the root itself is left boundary or right boundary. Note this definition only applies to the input binary tree, and not applies to any subtrees.

The left-most node is defined as a leaf node you could reach when you always firstly travel to the left subtree if exists. If not, travel to the right subtree. Repeat until you reach a leaf node.

The right-most node is also defined by the same way with left and right exchanged.


 */
// https://xiaoguan.gitbooks.io/leetcode/content/LeetCode/545-boundary-of-binary-tree-medium.html
//
class Solution {
    bool isLeaf(TreeNode *root) { return !root->left && !root->right; }
    void addLeaves(TreeNode *root, vector<int> &res) {
        if (isLeaf(root)) {
            res.push_back(root->val);
            return;
        }
        if (root->left)
            addLeaves(root->left, res);
        if (root->right)
            addLeaves(root->right, res);
    }

public:
  vector<int> boundaryOfBinaryTree(TreeNode *root) {
      if (!root)
          return {};

      vector<int> res;
      if (!isLeaf(root))
          res.push_back(root->val);
      // add left boundary
      TreeNode *cur = root->left;
      while (cur) {
          if (!isLeaf(cur)) {
              res.push_back(cur->val);
          }
          if (cur->left) {
              cur = cur->left;
          } else {
              cur = cur->right;
          }
      }
      // add leaf nodes
      addLeaves(root, res);

      cur = root->right;
      vector<int> tmp;
      // add right boundary
      while (cur) {
          if (!isLeaf(cur))
              tmp.push_back(cur->val);
          if (cur->right)
              cur = cur->right;
          else
              cur = cur->left;
      }
      for (int i = tmp.size() - 1; i >= 0; --i) {
          res.push_back(tmp[i]);
      }
      return res;
  }
};

int main() {

	Solution s;

	return 0;
}
