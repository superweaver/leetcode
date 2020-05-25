#include "common.h"
class Solution {
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        //vector<int> counter(10, 0);
        int counter = 0;
        int result = 0;
        dfs(root, counter, result);
        return result;
    }
private:
    void dfs(TreeNode* root, int& counter, int& result) {
        if (!root) {
            return;
        }
        counter ^= (1 << root->val);

        if (root->left) {
            dfs(root->left, counter, result);
        }
        if (root->right) {
            dfs(root->right, counter, result);
        }
        if (!root->left && !root->right) {
            if (!counter || !(counter & (counter - 1))) {
                result++;
            }
        }
        counter ^= (1 << root->val);
    }
};

class Solution1 {
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        vector<int> counter(10, 0);
        int result = 0;
        dfs(root, counter, result);
        return result;
    }
private:
    void dfs(TreeNode* root, vector<int>& counter, int& result) {
        if (!root) {
            return;
        }
        counter[root->val]++;

        if (root->left) {
            dfs(root->left, counter, result);
        }
        if (root->right) {
            dfs(root->right, counter, result);
        }
        if (!root->left && !root->right) {
            int single = 0;
            for (auto count : counter) {
                single += (count & 1);
            }
            if (single < 2) {
                result++;
            }
        }
        counter[root->val]--;
    }
};

int main() {

	Solution s;

	return 0;
}
