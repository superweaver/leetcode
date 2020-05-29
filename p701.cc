#include "common.h"
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root){return nullptr;}
        TreeNode* current = root;
        while(current) {
            if(current->val < val){
                if (current->right){
                     current = current->right;
                }
                else {
                    current->right = new TreeNode(val);
                    break;
                }

            } else {
                if (current->left){
                     current = current->left;
                }
                else {
                    current->left = new TreeNode(val);
                    break;
                }
            }
        }

        return root;
    }
};

int main() {

	Solution s;

	return 0;
}
