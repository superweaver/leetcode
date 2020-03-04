#include "common.h"
class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {        
        TreeNode dummy(1);
        dummy.left = root;        
        helper(dummy.left, target);        
        return dummy.left;
    }
    private:
    void helper(TreeNode*& root, int target){
        if (!root){
            return;
        }
        if (root->left){
            helper(root->left, target);
        }
        if (root->right){
            helper(root->right, target);
        }
        if (!root->left && !root->right && root->val == target){            
           // TreeNode* t = &(*root); delete t;            
            root = nullptr;
        }
    }
};

int main() {

	Solution s;

	return 0;
}
