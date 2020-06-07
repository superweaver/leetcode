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
    TreeNode* increasingBST(TreeNode* root) {
        if(!root) return root;
        stack<TreeNode*> s;
        TreeNode* result = nullptr;
        TreeNode* current = root;
        TreeNode* pre = nullptr;
        while(current || !s.empty()){
            while(current){
                s.push(current);
                current= current->left;
            }
            // current = nullptr
            current = s.top();
            current->left = nullptr;
            s.pop();
            if(result==nullptr){
                result = current;
            }
            if(pre){
                pre->right = current;
            }
            pre = current;
            current = current->right;
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
