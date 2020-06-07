#include "common.h"

class Solution {
  public:
    vector<TreeNode *> allPossibleFBT(int N) {
        // dp
        if (N % 2 == 0)
            return {};
        vector<vector<TreeNode *>> dp(N + 1, {nullptr});
        dp[1] = {new TreeNode(0)};
        for (int i = 2; i <= N; ++i) {
            if (i % 2 == 0)
                continue;
            dp[i] = {};
            int child = i - 1;
            // += 2
            for (int left = 1; left < child; left += 2) {
                int right = child - left;
                for (auto &lr : dp[left]) {
                    for (auto &rr : dp[right]) {
                        dp[i].push_back(new TreeNode(0));
                        auto &root = dp[i].back();
                        root->left = deepcopy(lr);
                        root->right = deepcopy(rr);
                    }
                }
            }
        }
        for (int i = 0; i < N; ++i) {
            for (auto &root : dp[i]) {
                erase(root);
            }
        }
        return dp[N];
    }

  private:
    TreeNode *deepcopy(TreeNode *root) {
        if (!root)
            return nullptr;
        TreeNode *node = new TreeNode(0);
        node->left = deepcopy(root->left);
        node->right = deepcopy(root->right);
        return node;
    }
    void erase(TreeNode *root) {
        if (!root) {
            return;
        }
        erase(root->left);
        erase(root->right);
        delete root;
    }
};

int main() {

	Solution s;

	return 0;
}
