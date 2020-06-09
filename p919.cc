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
class CBTInserter {
  public:
    CBTInserter(TreeNode *root) {
        // root is not null
        v.clear();
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int s = q.size();
            while(s--) {
                auto c = q.front();
                q.pop();
                v.push_back(c);
                if (c->left) {
                    q.push(c->left);
                }
                if (c->right) {
                    q.push(c->right);
                }
            }
        }
    }

    int insert(int value) {
        int i = v.size();
        v.push_back(new TreeNode(value));
        int p = (i - 1) / 2;
        if (p * 2 + 1 == i) { // left
            v[p]->left = v.back();
        } else { // right
            v[p]->right = v.back();
        }
        return v[p]->val;
    }
    TreeNode *get_root() { return v[0]; }

  private:
    vector<TreeNode*> v;
};

class CBTInserter2 {
  public:
    CBTInserter2(TreeNode *root) {
        // root is not null
        d_root = root;
        q.push(root);
        bool done = false;
        while (!done && !q.empty()) {
            size = q.size();
            while (size) {
                TreeNode *current = q.front();
                if (current->left && current->right) {
                    q.pop();
                    size--;
                    q.push(current->left);
                    q.push(current->right);
                } else {
                    if (current->left) {
                        q.push(current->left);
                    }
                    done = true;
                    break;
                }
            }
        }
    }

    int insert(int v) {
        TreeNode *current = q.front();
        if (!current->left) {
            current->left = new TreeNode(v);
            q.push(current->left);
        } else {
            current->right = new TreeNode(v);
            q.push(current->right);
            q.pop();
            size--;
            if (!size) {
                size = q.size();
            }
        }
        return current->val;
    }

    TreeNode *get_root() { return d_root; }

  private:
    TreeNode *d_root;
    queue<TreeNode *> q;
    size_t size;
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */

int main() {

    Solution s;

    return 0;
}
