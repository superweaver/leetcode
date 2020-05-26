#include "common.h"
class Solution {
  public:
    int findBottomLeftValue(TreeNode *root) {
        queue<TreeNode *> q;
        // in nature, this is a level order traversal
        // but right-to-left level order traversal
        q.push(root);
        while (!q.empty()) {
            root = q.front();
            q.pop();
            if (root->right) {
                q.push(root->right); // nice!
            }
            if (root->left) {
                q.push(root->left);
            }
        }
        return root->val;
    }
};

int main() {

    Solution s;

    return 0;
}
