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
class Solution_my {
    // not a general solution
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        //Each node in the tree has unique values 0 <= node.val <= 500
        // convert tree to graph, then do BFS
        if (K == 0) return {target->val};
        const int N = 501;
        vector<unordered_set<int>> graph(N);
        mark(graph, root);
        vector<bool> visited(N, false);
        vector<int> current = { target->val };
        visited[target->val] = true;
        vector<int> next;
        int k = 0;
        while(!current.empty()) {
            if(k == K) return current;
            next.clear();
            for(auto c : current) {
                for(auto n : graph[c]) {
                    if (!visited[n]) {
                        visited[n] = true;
                        next.push_back(n);
                    }
                }
            }
            current.swap(next);
            k++;
        }
        return {};
    }
private:
    void mark(vector<unordered_set<int>>&graph, TreeNode*root) {
        if (!root) {
            return ;
        }
        if(root->left) {
            graph[root->val].insert(root->left->val);
            graph[root->left->val].insert(root->val);
        }
        if (root->right) {
            graph[root->val].insert(root->right->val);
            graph[root->right->val].insert(root->val);
        }
        mark(graph, root->right);
        mark(graph, root->left);
    }
};

class Solution {
public:
     vector<int> ans;

     void boob(TreeNode *root, int k) {
         if (root == NULL) {
             return;
         }
         if (k == 0) {
             ans.push_back(root->val);
         }
         boob(root->left, k - 1);
         boob(root->right, k - 1);
     }

     int f(TreeNode *root, TreeNode *target, int k) {
         if (root == NULL) {
             return -1;
         }

         if (root == target) {
             boob(root, k); // going down and use target as root
             return 0; // nice
         }

         int ld = f(root->left, target, k);

         if (ld != -1) {
             if (ld + 1 == k) { // target is k distance away from root, root is the root of subtree
                 ans.push_back(root->val);
             } else {
                 // turn to root->right, the proper distance is k - 2 -ld
                 boob(root->right, k - 2 - ld);
             }
             return ld + 1;
        }

        int rd = f(root->right, target, k);

        if (rd != -1) {
            if (rd + 1 == k) {
                ans.push_back(root->val);
            } else {
                boob(root->left, k - 2 - rd);
            }
            return rd + 1;
        }
        return -1;
     }

     vector<int> distanceK(TreeNode *root, TreeNode *target, int K) {
         if (root == NULL || target == NULL || K < 0) {
             return ans;
         }
         f(root, target, K);
         return ans;
     }
};

int main() {

	Solution s;

	return 0;
}
