#include "common.h"
class Solution {
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
		// n is odd
		// fuck, only neighbor can be picked.
		vector<int> counter(n + 1, 0);
		vector<TreeNode*> self(n + 1, 0);
		vector<TreeNode*> parent(n + 1, nullptr);
		dfs(root, counter, parent, self);
		return check(root, x, counter, parent, self);
    }

private:
    int dfs(TreeNode* root, vector<int>& counter, vector<TreeNode*>& parent,
            vector<TreeNode*>& self)
    {
        if (!root) {
			return 0;
		}
		int v = root->val;	
		int n = 1;
		if (root->left) {
			parent[root->left->val] = root;
			n += dfs(root->left, counter, parent, self);
		}
		if (root->right) {
			parent[root->right->val] = root;
			n += dfs(root->right, counter, parent, self);
		}
		self[v] = root;
		return counter[v] = n;
    }
    bool check(TreeNode* root, int firstPick, vector<int>& counter, vector<TreeNode*>& parent,
               vector<TreeNode*>& self)
    {
        // assume first play choose "firstPick"
        // what is the best option should second player choose
        // there are at most three ways to choose
        TreeNode* p = parent[firstPick];
        TreeNode* node = self[firstPick];
        TreeNode* l = node->left;
        TreeNode* r = node->right;
        int total = counter[root->val];
		int candidate = p ? total - counter[firstPick] : 0;
		candidate = max(candidate, l ? counter[l->val] : 0);
		candidate = max(candidate, r ? counter[r->val] : 0);
		return candidate > total - candidate;
		/*	
        if (!p) {  // root->val == firstPick
            if (!l && !r) {
                return false;
            } else if (l && !r) {
                return counter[l->val] > 1;
                // return  true;
            } else if (!l && r) {
                return counter[r->val] > 1;
            } else {
                int left = counter[l->val];
                int right = counter[r->val];
                return (left > 1 + right) || (right > 1 + left);
            }
        } else {
            // p is not null
            if (!l && !r) {
                // pick parents
                return total - 1 > 1;
            } else if (l && !r) {
                int node_from_parent = total - counter[firstPick];
                int left = counter[l->val];
                return (node_from_parent > left + 1) || (left > node_from_parent);
            } else if (r && !l) {
                int node_from_parent = total - counter[firstPick];
                int right = counter[r->val];
                return (node_from_parent > right + 1) || (right > node_from_parent);
            } else {
				int tmp  = -1;
                tmp = max(tmp,  total - counter[firstPick]);
                tmp = max(tmp, counter[r->val]);
                tmp = max(tmp, counter[l->val]);
				// only neighbor can be picked;
                return tmp > (total - tmp);
            }
        }
		*/
    }
};

int main()
{

	string str = "1,2,3,4,5,6,7,8,9,10,11";
	int n = 11, x = 3;
	str = "1,2,3,4,5";
	n = 5;
	x = 2;
    Solution s;
	Codec codec;
	auto root = codec.deserialize(str);
	cout << s.btreeGameWinningMove(root, n, x) << endl;
	deleteTree(root);
    return 0;
}
