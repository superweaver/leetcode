#include "common.h"
class Solution {
    // dfs is faster
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        auto p = getDeepestTree(root, 0);
        return p.second;
    }

private:
  pair<int, TreeNode *> getDeepestTree(TreeNode *root, int h) {
      if (root == NULL) {
          return {h, NULL};
      }
      auto l = getDeepestTree(root->left, h + 1);
      auto r = getDeepestTree(root->right, h + 1);

      // !!! nice return value
      return {max(l.first, r.first),
              l.first == r.first ? root : l.first > r.first ? l.second : r.second};
  }
};

int main() {

	Solution s;

	return 0;
}
