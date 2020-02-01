#include "common.h"
class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
		vector<TreeNode*> result;
		if (!root || to_delete.empty()) {
			return {root};
		}
		vector<bool> d_set(1001, false);

		for(auto d : to_delete) {
			d_set[d] = true;
		}
		helper(root, d_set, result);
		if (root) {
			result.push_back(root);
		}
		return result;
    }
private:
	TreeNode* helper(TreeNode*& root, vector<bool>& d_set, vector<TreeNode*>& result) {
		if(!root)  {
			return root;
		}
		auto l = helper(root->left, d_set, result);
		auto r = helper(root->right, d_set, result);
		if (d_set[root->val]) {
			if (l) {
				result.push_back(l);
			}
			if (r) {
				result.push_back(r);
			}
			d_set[root->val] = false;
			root = nullptr;
		}// else { // do nothing} 
		return root;
	}
};
int main() {

	Codec codec;
	auto root = codec.deserialize("1,2,3,4,5,6,7");
	Solution s;
	vector<int> to_delete = {3, 5};
	auto r = s.delNodes(root, to_delete);
	TreeUtil tu;
	for( auto pr : r) {
		tu.printTree(pr);
	}

	return 0;
}
