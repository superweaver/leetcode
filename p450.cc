#include "common.h"
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->val < key) {
           root->right = deleteNode(root->right, key);
        } else if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else {
            // delete this node;
            if (root->right) {
                // find the smallest in the right subtree
                TreeNode* current = root->right;
                while(current->left) {
                    current = current->left;
                }
                root->val = current->val;
                root->right = deleteNode(root->right, root->val); // !! trick
            } else {
                root = root->left;
            }
        }
        return root;
    }
};
class Solution_manual {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->val < key) {
           root->right = deleteNode(root->right, key);
        } else if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else {
            // delete this node;
            root = removeNode(root);
            }
        return root;
    }
private:
    TreeNode* removeNode(TreeNode* node) {
        if(!node) return node;
        if (node->right) {
            TreeNode* pre = nullptr;
            TreeNode* current = node->right;
            while(current->left) {
                pre = current;
                current = current->left;
            }
            if (pre) {
                pre->left = nullptr;
                current->left = node->left;
                TreeNode* right = current;
                while(right->right) {
                    right = right -> right;
                }
                right->right = node->right; // node->right->val > right->val
                delete node;
                node = current;
            } else {
                current->left = node->left;
                delete node;
                node = current;
            }
        } else if (node->left) {
            TreeNode* pre = nullptr;
            TreeNode* current = node->left;
            while(current->right) {
                pre = current;
                current = current->right;
            }
            if (pre) {
                pre->right = nullptr;
                current->right = node->right;
                TreeNode* left = current;
                while(left->left) {
                    left = left -> left;
                }
                left->left = node->left;  // node->left->val < left->val
                delete node;
                node = current;
            } else {
                current->right = node->right;
                delete node;
                node = current;
            }
        } else {
            delete node;
            node = nullptr;
        }
        return node;
    }
};

int main() {

	Solution s;

	return 0;
}
