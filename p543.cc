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
// the longest path (# of edgds) in the tree
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int result = 0;
        helper(root, result);
        return result;
    }
private:
    int helper(TreeNode* node, int& result) {
        if (node) {
            int l = helper(node->left, result);
            int r = helper(node->right, result);
            int maxNode = max(l, r) + 1;
            // edges is the # of edges for possible path whose root is node
            int edges = l + r; // l + r + 1(self node) - 1
            result = max(result, edges);
            return maxNode;
            // return the max # of node that ends at node
        }
        return 0;
    }
};


int main() {

	Solution s;

	return 0;
}
