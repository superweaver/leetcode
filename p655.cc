#include "common.h"

class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
        if (!root){
            return {};
        }
        pair<int, int> wh = getWidthHeight(root);
        int R = wh.second;
        int C = wh.first;
        vector<vector<string> > result(R, vector<string>(C, ""));
        int r = 0;
        int c = (C - 1) / 2;
        print(result, root, r, c, C, R);
        return result;
    }

private:
        pair<int, int> getWidthHeight(TreeNode* root){
            if(!root) return {0, 0};
            pair<int, int> pl = getWidthHeight(root->left);
            pair<int, int> pr = getWidthHeight(root->right);
            return { 1 + 2 * max(pl.first, pr.first), 1 + max(pl.second, pr.second) };
        }
        void print(vector<vector<string> >& result, TreeNode* root, int r, int c, int w, int h)
        {
            if(!root) return;
            result[r][c] = to_string(root->val);
            int nextw = (w - 1) / 2;
            int nexth = h - 1;
            if (root->left) {
                print(result, root->left, r + 1, c - (nextw + 1) / 2, nextw, nexth);
            }
            if (root->right) {
                print(result, root->right, r + 1, c + (nextw + 1) / 2, nextw, nexth);
            }
        }
};

int main() {

	Solution s;

	return 0;
}
