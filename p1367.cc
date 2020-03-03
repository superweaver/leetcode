#include "common.h"
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
		if (!head) return true;
		vector<int> target;
		auto c = head;
		while(c) {
			target.push_back(c->val);
            c = c->next;
        }
		vector<int> path;
		return helper(root, target, path);
	}
private:
    bool helper(TreeNode* root, const vector<int>& target, vector<int>& path)
    {
        if (path.size() >= target.size()) {
			bool found = true;
            for (int i = path.size() -1 , j = target.size()-1; i >= 0 && j >= 0; --i, --j) {
                if (path[i] != target[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
				return true;
			}
        }
		if (!root) {
			return false;
		}
		path.push_back(root->val);
		if (helper(root->left, target, path)) {
			return true;
		}
		if (helper(root->right, target, path)) {
			return true;
		}
		path.pop_back();
		return false;
    }
};




int main() {
	vector <int> L {1,4,2,6};
	string Tree("1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3");
	Codec codec;
	auto root = codec.deserialize(Tree);
	auto head = buildList(L);
	displaylist(head);
	TreeUtil tu;
	tu.printTree(root);

	Solution s;
	cout << s.isSubPath(head, root) << endl;
    deleteTree(root);
    deleteList(head);
    return 0;
}
