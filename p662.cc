#include "common.h"
// https://leetcode.com/problems/maximum-width-of-binary-tree/discuss/106645/C%2B%2BJava-*-BFSDFS3liner-Clean-Code-With-Explanation
//
// The binary tree has the same structure as a full binary tree, but some nodes are null.
//
// The width of a tree is the maximum width among all levels.
// :( include leaves or non-leaves
class Solution {
public:
	int widthOfBinaryTree(TreeNode* root)
	{
		if (!root) {
			return 0;
		}
		TreeNode* parent = nullptr;
		int height = 0;
		result = 1;
		left = vector<unsigned int>(32, UINT_MAX);
		right = vector<unsigned int>(32, 0);
		helper(root, parent, 0, height);
		return result;
		}

private:
	vector<unsigned int> left;
	vector<unsigned int> right;
	unsigned int result;
	void helper(TreeNode* root, TreeNode* parent, unsigned int pindex, int height)
	{
		if (!root) {
			return;
		}
		if (height == 32) {
			// restart from here
            // otherwise, there will be overflow
			parent = nullptr;
			height = 0;
			pindex = 0;
			left = vector<unsigned int>(32, UINT_MAX);
			right = vector<unsigned int>(32, 0);
			helper(root, parent, pindex, height);
		}
		else {
			unsigned int index = 0;
			if (!parent) {
				// parent == nullptr
				// skip all width == 1 layers
				if (root->left && (!root->right)) {
					helper(root->left, parent, pindex, height);
					return; // must return;
				}
				else if (root->right && (!root->left)) {
					helper(root->right, parent, pindex, height);
					return; // must return;
				}
				else {
					parent = root;
					index = 0;
					//height = 0;
				}
			}
			else {
				index =
					(parent->left && parent->left == root) ? ((pindex << 1) + 1) : ((pindex << 1) + 2);
			}
			left[height] = min(index, left[height]);
			right[height] = max(index, right[height]);
			result = max(right[height] - left[height] + 1, result);
			parent = root;
			if (root->left || root->right) {
				height++;
			}
			if (root->left) {
				helper(root->left, parent, index, height);
			}
			if (root->right) {
				helper(root->right, parent, index, height);
			}
		}
	}
};
class Solution_overflow {
  public:
    int widthOfBinaryTree(TreeNode *root) {
        // assign an index to node
        if (!root) {
            return 0;
        }
        queue<pair<TreeNode *, int>> q; // pointer and node index
        q.push({root, 1});
        int result = 0;
        while (!q.empty()) {
            int size = q.size();
            int leftindex = q.front().second;
            int rightindex = leftindex;
            while (size--) {
                auto current = q.front();
                q.pop();
                auto pc = current.first;
                rightindex = current.second;
                if (pc->left) {
                    // this will cause rightinde overflow
                    q.push({pc->left, (rightindex << 1)});
                }
                if (pc->right) {
                    q.push({pc->right, 1 + (rightindex << 1)});
                }
            }
            result = max(result, rightindex - leftindex + 1);
        }
        return result;
    }
};
int main() {

    Solution s;

    return 0;
}
