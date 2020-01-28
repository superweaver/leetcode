#include "common.h"
class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        //if (!root) { return root; }
        vector<TreeNode*> deepestLeaves;
        vector<TreeNode*> parents(1001, nullptr); // act as a unordered_map<int, TreeNode*>
        int globalDepth = -1;
        helper(root, deepestLeaves, parents, 0, globalDepth); 
        while(deepestLeaves.size() > 1) {
            vector<TreeNode*> upperLevel;
            for(auto&p:deepestLeaves) {
                auto up = parents[p->val];
                if (upperLevel.empty() || upperLevel.back() != up) {
                    upperLevel.push_back(up);
                }
            }
            deepestLeaves.swap(upperLevel);
        }
        return deepestLeaves.front();
    }
    private:
        void helper(TreeNode* root, vector<TreeNode*>& deepestLeaves, vector<TreeNode*>& parents, int currentDepth, int&globalDepth) {
            if (!root) return;
            if (root->left) {
                parents[root->left->val] = root;
            }
            if (root->right) {
                parents[root->right->val] = root;
            }
            if (!root->left && !root->right ) {
                if (currentDepth > globalDepth) {
                    globalDepth = currentDepth;
                    deepestLeaves.clear();
                    deepestLeaves.push_back(root);
                } else if (currentDepth == globalDepth) {
                    deepestLeaves.push_back(root); 
                }
            }
            if (root->left) {
                helper(root->left, deepestLeaves, parents, currentDepth + 1, globalDepth);
            }
            if (root->right) {
                helper(root->right, deepestLeaves, parents, currentDepth + 1, globalDepth);
            }
        }

};

