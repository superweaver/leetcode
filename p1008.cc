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
    TreeNode *bstFromPreorder(vector<int> &preorder) {
        int n = preorder.size();
        vector<int> v(preorder);
        sort(v.begin(), v.end());
        unordered_map<int, int> cache;
        for (int i = 0; i < n; ++i) {
            cache[v[i]] = i;
        }
        return helper(preorder, 0, n - 1, 0, n - 1, cache);
    }

  private:
    TreeNode *helper(vector<int> &preorder, int p_start, int p_end, int v_start, int v_end,
                     unordered_map<int, int> &cache) {
        if (p_end < p_start) {
            return nullptr;
        }
        if (p_start == p_end) {
            return new TreeNode(preorder[p_start]);
        }
        TreeNode *root = new TreeNode(preorder[p_start]);
        int iv_root = cache[preorder[p_start]];
        int left_len = iv_root - v_start;
        int right_len = v_end - iv_root;
        root->left = helper(preorder, p_start + 1, p_start + left_len, v_start, iv_root - 1, cache);
        root->right = helper(preorder, p_end - right_len + 1, p_end, iv_root + 1, v_end, cache);
        return root;
    }
};

int main() {

    Solution s;

    return 0;
}
