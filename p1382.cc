#include "common.h"
class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
		vector<int> values;
		getvalues(values, root);
		int n = values.size();
		return  buildBST(values, 0, n - 1);		
    }
private:
	void getvalues(vector<int>& values, TreeNode*root) {
		if (!root) {
			return;
		}
		getvalues(values, root->left);
		values.push_back(root->val);
		getvalues(values, root->right);
	}
	TreeNode *buildBST(vector<int>& values, int start, int end) {
		int len = end - start + 1;
		if (len == 0) {
			return nullptr;
		}
        int mid = start + len / 2;
		TreeNode * root = new TreeNode(values[mid]);
		root->left = buildBST(values, start, mid - 1);
		root->right = buildBST(values, mid+1, end);
       return root; 
	}
};

int main() {

	Solution s;

	return 0;
}
