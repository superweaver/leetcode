#include "common.h"
// https://leetcode.com/problems/two-sum-iv-input-is-a-bst/discuss/106063/C%2B%2B-Clean-Code-O(n)-time-O(lg-n)-space-BinaryTree-Iterator

class BSTIterator {
    stack<TreeNode *> s;
    TreeNode *node;
    bool forward;

  public:
    BSTIterator(TreeNode *root, bool forward) : node(root), forward(forward){};
    bool hasNext() { return node != nullptr || !s.empty(); }
    int next() {
        while (node || !s.empty()) {
            if (node) {
                s.push(node);
                node = forward ? node->left : node->right;
            } else {
                node = s.top();
                s.pop();
                int nextVal = node->val;
                node = forward ? node->right : node->left;
                return nextVal;
            }
        }

        return -1; // never reach & not necessary
    }
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;
        BSTIterator l(root, true);
        BSTIterator r(root, false);
        for (int i = l.next(), j = r.next(); i < j;) {
            int sum = i + j;
            if (sum == k) {
                return true;
            }
            else if (sum < k) {
                i = l.next();
            }
            else {
                j = r.next();
            }
        }
        return false;
    }
};
int main() {

	Solution s;

	return 0;
}
