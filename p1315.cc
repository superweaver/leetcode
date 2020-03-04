#include "common.h"
class Solution {
public:
    int sumEvenGrandparent(TreeNode* root) {
        int sum = 0;
        helper(nullptr, nullptr, root, sum);
        return sum;
    }
    private:
    void helper(TreeNode* pp, TreeNode* p, TreeNode* root, int& sum){
        if (!root){
            return;
        }
        if (pp && !(pp->val&1)){
            sum += root->val;
        }
        if (root->left){
            helper(p, root, root->left, sum);
        }
        if (root->right){
            helper(p, root, root->right, sum);
        }
    }
};

int main() {

	Solution s;

	return 0;
}
