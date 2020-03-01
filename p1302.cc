#include "common.h"
class Solution {
public:
    int deepestLeavesSum(TreeNode* root)
    {
        int sum = 0;
        int depth = 0;  // deepest
        helper(sum, depth, 0, root);
        return sum;
    }

private:
    void helper(int& sum, int& depth, int current, TreeNode* root)
    {
        if (!root) {
            return;
        }

        if (root->left) {
            helper(sum, depth, current + 1, root->left);
        }
        if (root->right) {
            helper(sum, depth, current + 1, root->right);
        }
        if (!root->left && !root->right) {
            if (current > depth) {
                sum = root->val;
                depth = current;
            } else if (current == depth) {
                sum += root->val;
            }
        }
    }
};

int main()
{

    Solution s;

    return 0;
}
