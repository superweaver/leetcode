#include "common.h"
class Iter {
	public:
    Iter(TreeNode* r)
    {
        root = r;
    }
    TreeNode* Next() {
		while(root || !s.empty()) {
			while(root){
				s.push(root);
				root = root->left;
			}
			auto result = s.top();
			s.pop();
			root = result ->right;
			return result;
		}
		return nullptr;
	}
	private:
	TreeNode* root;
    stack<TreeNode*> s;
};
class Solution {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
		// bst
		// preorder traversal
		vector<int> result;
		Iter it1(root1);
		Iter it2(root2);
		auto n1 = it1.Next();
        auto n2 = it2.Next();
        while(true) {
			if (!n1 && !n2) {
				break;
			}
			auto v1 = (n1 == nullptr ? INT_MAX : n1->val);
			auto v2 = (n2 == nullptr ? INT_MAX : n2->val);
			if (v1 < v2) {
                result.push_back(v1);
                n1 = it1.Next();
            } else if (v1 > v2) {
                result.push_back(v2);
                n2 = it2.Next();
			} else {
                result.push_back(v1);
                result.push_back(v2);
                n1 = it1.Next();
				n2 = it2.Next();
			}
		}
		return result;
    }
};

int main() {

	Solution s;

	return 0;
}
