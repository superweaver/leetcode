#include "common.h"
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  public:
    // Input: "1-2--3---4-5--6---7"
    // Output: [1,2,5,3,null,6,null,4,null,7]
    TreeNode *recoverFromPreorder(string S) {
        size_t i = 0;
        pair<int, int> p_root = getNode(S, i);
        stack<pair<TreeNode *, int>> s; // second is the depth of first
        TreeNode *root = new TreeNode(p_root.first);
        s.push({root, p_root.second});

        while (!s.empty() && i < S.size()) {
            auto next = getNode(S, i);
            while (!s.empty() && s.top().second != next.second - 1) {
                s.pop();
            }
            auto nextNode = new TreeNode(next.first);
            if (!s.top().first->left) {
                s.top().first->left = nextNode;
            } else {
                s.top().first->right = nextNode;
            }
            s.push({nextNode, next.second});
        }
        return root;
    }

  private:
    pair<int, int> getNode(string &S, size_t &i) {
        if (i == S.size()) {
            return {INT_MIN, INT_MIN};
        }
        int d = 0;
        while (i < S.size() && S[i] == '-') {
            i++;
            d++;
        }
        int v = 0;
        while (i < S.size() && S[i] != '-') {
            v = 10 * v + S[i] - '0';
            i++;
        }
        return {v, d};
    }
};

int main() {

	Solution s;

	return 0;
}
