#include "common.h"
class Solution {
  public:
    TreeNode *trimBST(TreeNode *root, int L, int R) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->val < L) {
            return trimBST(root->right, L, R);
        }
        if (root->val > R) {
            return trimBST(root->left, L, R);
        }
        // note : root is within Range[L, R]
        // keep root;
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
    }
};

int main() {

    Solution s;

    return 0;
}
