#include "common.h"
class Solution {
  public:
    bool flipEquiv(TreeNode *root1, TreeNode *root2) {
        if (!root1 && !root2) {
            return true;
        }
        if ((root1 && !root2) || (!root1 && root2)) {
            return false;
        }
        if (root1->val != root2->val) {
            return false;
        }
        return (flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right)) ||
               (flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left));
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution2 {
public:
	bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        // Each tree will have at most 100 nodes.
        // Each value in each tree will be a unique integer in the range[0, 99].
        if (!root1 && root2) {
            return false;
        }
        if (root1&&!root2) return false;
		if (!root1 && !root2) return true;
		if (root1->val != root2->val) return false;
		vector<int> parents1(100, -1);
		parents1[root1->val] = -2;
		helper(root1, parents1, parents1[root1->val]);
		vector<int> parents2(100, -1);
		parents2[root2->val] = -2;
		helper(root2, parents2, parents2[root1->val]);
		for (int i = 0; i < 100; ++i) {
			if (parents1[i] != parents2[i]) {
				return false;
			}
		}
		return true;
	}
private:
	void helper(TreeNode*root, vector<int>& parents, int pv) {
		if (root) {
			parents[root->val] = pv;
			helper(root->left, parents, root->val);
			helper(root->right, parents, root->val);
		}
	}
	/*
	bool helper2(TreeNode* root, const vector<int>&parents, int pv) {
		if (!root) return true;
		if (parents[root->val] != pv) {
			return false;
		}
		return helper2(root->left, parents, root->val) && helper2(root->right, parents, root->val);
	}
	*/
};


int main() {

	Solution s;

	return 0;
}
