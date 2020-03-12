#include "common.h"
class Solution {
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		if (!original) {
			return nullptr;
		}
		// inorder traversal
		stack<TreeNode*> so;
        stack<TreeNode*> st;
		TreeNode* co = original;
		TreeNode* ct = cloned;
		while(co || !so.empty()) {
			while(co) {
				so.push(co);
				st.push(ct);
				co = co->left;
				ct = ct->left;
			}
			co = so.top();
			so.pop();
			ct = st.top();
			st.pop();
			if (co == target) {
				return ct;
			} else {
				co = co->right;
				ct = ct->right;
			}
		}
		return nullptr;
    }
};

int main() {
    string tree = "7,4,3,null,null,6,19";
    int target = 3;
	Codec codec;
	auto r1 = codec.deserialize(tree);
	auto r2 = codec.deserialize(tree);

    Solution s;
	cout << s.getTargetCopy(r1, r2, r1->right)->val << endl;

	deleteTree(r1);
	deleteTree(r2);

	return 0;
}
