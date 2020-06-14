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
    TreeNode *sufficientSubset(TreeNode *root, int limit) {
        helper(root, limit, 0);
        return root;
    }

  private:
    int helper(TreeNode *&root, int limit, int prefix_sum) {
        if (!root) {
            return 0;
        }
        prefix_sum += root->val;
        if (!root->left && !root->right) {
            int ret_value = root->val;
            if (prefix_sum < limit) {
                auto t = root;
                root = nullptr;
                delete t;
            }
            return ret_value;
        }
        int v = INT_MIN;
        if (root->left) {
            int l = helper(root->left, limit, prefix_sum);
            v = max(l, v);
        }
        if (root->right) {
            int r = helper(root->right, limit, prefix_sum);
            v = max(r, v);
        }
        prefix_sum += v;
        int ret_value = v + root->val;
        if (prefix_sum < limit) {
            auto t = root;
            root = nullptr;
            delete t;
        }
        return ret_value;
    }
};

int main() {

    Solution s;

    return 0;
}
