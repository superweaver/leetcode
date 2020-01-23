#ifndef _COMMON_H_
#define _COMMON_H_
#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <set>
#include <climits>
#include <sstream>
#include <cassert>
#include <chrono>  // for high_resolution_clock
#include <string>
#include <cstdio>
#include <cstring>
#include <deque>
#include <list>
#include <bitset>
#include <random>
#include <iomanip>
using namespace std;

template <class T> void displayvector(vector<T> v, bool reverse = false)
{
    if (reverse) {
        for (auto it = v.rbegin(); it != v.rend(); ++it) {
            cout << *it << " ";
        }
    }
    else {
        for (auto it = v.begin(); it != v.end(); ++it) {
            cout << *it << " ";
        }
    }
    cout << endl;
}
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
  };
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void displaylist(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}
ListNode * buildList(vector<int> nums) {
   size_t N = nums.size();
   if (N == 0) return nullptr;
   ListNode* head = new ListNode(nums[0]);
   ListNode* prev = head;
   for(size_t i = 1; i < N; ++i) {
       prev->next = new ListNode(nums[i]);
       prev = prev->next;
   }
   return head;


}
void deleteList (ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

vector<int> preOrderStack(TreeNode* root) {
    vector<int> result;
    if(root == nullptr) {
        return result;
    }
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        result.push_back(node->val);
        if (node->right != nullptr) {
            s.push(node->right);
        }
        if (node->left != nullptr) {
            s.push(node->left);
        }
    }
    return result;
}
vector<int> preOrderMoris(TreeNode* root) {
    vector<int> result;
    if(root == nullptr) {
        return result;
    }
    stack<TreeNode*> s;
    TreeNode* prev = nullptr;
    // prev is only used for store node before current
    // it can be used for solving some issues
    TreeNode* current = root;
    while (current != nullptr) {
        if (current->left == nullptr) {
            // visit current
            result.push_back(current->val);
            prev = current;
            current = current->right;
        } else {
            TreeNode* node = current->left;
            while (node->right != nullptr && node->right != current) {
                node = node->right;
            }
            if (node->right == nullptr) {
                // set up thread before visiting current
                node->right = current;
                result.push_back(current->val);
                prev = current;
                current = current->left;
            }
            else {
                // current has been visited;
                // delete thread
                // go to current->right
                // no update for prev
                node->right = nullptr;
                current = current->right;
            }
        }
    }
    return result;

}
/*
 * InOrder traversal
1) Create an empty stack S.
2) Initialize current node as root
3) Push the current node to S and set current = current->left until current is NULL
4) If current is NULL and stack is not empty then
     a) Pop the top item from stack.
     b) Print the popped item, set current = popped_item->right
     c) Go to step 3.
5) If current is NULL and stack is empty then we are done.
*/
vector<int> inOrderStack(TreeNode* root) {
    // termination condition is current is nullptr and stack is empty()
    vector<int> result;
    if (root == nullptr) {
        return result;
    }
    TreeNode* current = root;
    stack<TreeNode*> s;
    while (current != nullptr || !s.empty()) {
        if (current != nullptr) {
            s.push(current);
            current = current->left;
        } else {
            // stack is not empty
            current = s.top();
            s.pop();
            result.push_back(current->val);
            current = current->right; // null or not doesn't matter
        }
    }
    return result;
}
vector<int> inOrderMoris(TreeNode* root) {
    vector<int> result;
    if (root == nullptr) {
        return result;
    }
    TreeNode* prev = nullptr;
    TreeNode* current = root;
    while (current != nullptr) {
        if (current->left == nullptr) {
            // we should visit current node
            result.push_back(current->val);
            prev = current;
            current = current->right;
        } else {
            TreeNode * node = current->left;
            // find the right most of subtree
            while(node->right != nullptr && node->right != current) {
                node = node->right;
            }
            if (node->right == nullptr) {
                // set up thread before visiting this current
                node->right = current;
                // no update for prev, since we are not visiting current in the first time
                current = current->left;
            }
            else {
                // node->right == current at this moment
                // visit current and delete thread
                node->right = nullptr;
                result.push_back(current->val);
                prev = current;
                current = current->right; // visit current before visiting it right
            }
        }
    }
    return result;
}
void  levelOrderQueue_display(TreeNode * root) {
    vector<int> result;
    if (root == nullptr) {
        return ;
    }
    queue<TreeNode*> q;
    q.push(root);
    q.push(nullptr); // separater
    int level = 0;
    while(!q.empty()) { // we have element in below layer
        result.clear();
        cout << level << ":";
        ++level;
        while(q.front() != nullptr) {
            TreeNode* node = q.front();
            q.pop();
            result.push_back(node->val);
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        q.pop();           // pop the separater of previous layer
        if (!q.empty()) {  // no more layer
            q.push(nullptr);
        }
        displayvector(result);
    }
}

vector<int> levelOrderQueue(TreeNode * root) {
    vector<int> result;
    if (root == nullptr) {
        return result;
    }
    queue<TreeNode*> q;
    q.push(root);
    q.push(nullptr); // separater
    while(!q.empty()) { // we have element in below layer
        if (q.front() != nullptr) {
            TreeNode* node = q.front();
            q.pop();
            result.push_back(node->val);
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        } else {
            q.pop(); // pop the separater of previous layer
            if (!q.empty()) { // no more layer
            q.push(nullptr);
            }
        }
    }
    return result;
}
vector<vector<int>> levelOrderQueue2(TreeNode * root) {
    vector<vector<int>> result;
    if (root == nullptr) {
        return result;
    }
    queue<TreeNode*> q;
    q.push(root);
    q.push(nullptr); // separater
    while(!q.empty()) { // we have element in below layer
        vector<int> layer;
        while (q.front() != nullptr) {
            TreeNode* node = q.front();
            q.pop();
            layer.push_back(node->val);
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        result.push_back(layer);
        q.pop();           // pop the separater of previous layer
        if (!q.empty()) {  // no more layer
            q.push(nullptr);
        }
    }
    return result;
}
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    return;
}

vector<int> postOrderStack(TreeNode* root)
{
    // method 2: stack
    stack<TreeNode*> s;
    vector<int> result;
    TreeNode *cur, *pre;  // cur is being visted , pre has been visited
    cur = root;
    pre = nullptr;

    while (cur != nullptr || !s.empty()) {
        while (cur != nullptr) {
            s.push(cur);
            cur = cur->left;  // go left;
        }
        // now cur is nullptr
        cur = s.top();
        if (cur->right == nullptr || cur->right == pre) {
            // visit cur
            result.push_back(cur->val);
            s.pop();
            pre = cur;
            cur = nullptr;  // important;
        } else {
            cur = cur->right;
        }
    }
    return result;
}

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        string result;
        if (root == nullptr)
            return result;
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);

        ostringstream oss;
        oss << root->val << ',';
        result += oss.str();

        while (!q.empty()) {
            string lastlayer;
            while (q.front() != nullptr) {
                TreeNode* current = q.front();
                q.pop();
                if (current->left) {
                    ostringstream oss;
                    oss << current->left->val << ',';
                    lastlayer += oss.str();
                    q.push(current->left);
                } else {
                    lastlayer += "null,";
                }
                if (current->right) {
                    ostringstream oss;
                    oss << current->right->val << ',';
                    lastlayer += oss.str();
                    q.push(current->right);
                } else {
                    lastlayer += "null,";
                }
            }
            q.pop();
            if (!q.empty()) {
                result += lastlayer;  // otherwise, lastlayer are all "null"
                q.push(nullptr);
            }
        }
        result.pop_back();  // the last ','
        while (result.size() >= 5 && result.substr(result.size() - 5) == ",null") {
            result = result.substr(0, result.size() - 5);
        }
        // it is possible there are several null
        return result;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
//    string str = "1,2,3,4,null,2,4,null,null,4";

        int n = data.size();
        if (n == 0)
            return nullptr;
        queue<string> sq;
        size_t start = 0;
        while (start < data.size()) {
            size_t end = data.find_first_of(',', start);
            string sub = data.substr(start, end - start);
            //cout << sub << endl;
            sq.push(sub);
            if (end == string::npos) {
                break;
            } else {
                start = end + 1;
            }
        }
        queue<TreeNode*> tq;
        ostringstream oss;
        oss << INT_MIN;
        string INTMINSTR = oss.str();
        TreeNode* root = constructTreeNode(sq.front(), INTMINSTR);
        tq.push(root);
        tq.push(nullptr);
        sq.pop();
        while (!sq.empty()) {
            while (tq.front() != nullptr) {
                TreeNode* current = tq.front();
                tq.pop();
                TreeNode* pl = nullptr;
                if (!sq.empty()) {
                    pl = constructTreeNode(sq.front(), INTMINSTR);
                    sq.pop();
                }
                if (pl) {
                    current->left = pl;
                    tq.push(pl);
                }
                TreeNode* pr = nullptr;
                if (!sq.empty()) {
                    pr = constructTreeNode(sq.front(), INTMINSTR);
                    sq.pop();
                }
                if (pr) {
                    current->right = pr;
                    tq.push(pr);
                }
            }
            tq.pop();
            if (!tq.empty()) {
                tq.push(nullptr);
            }
        }
        return root;
    }

private:
    TreeNode* constructTreeNode(string nodestr, const string& INTMINSTR)
    {
        if (nodestr == "null")
            return nullptr;
        int temp = 0;
        int sign = 1;
        size_t i = 0;

        if (nodestr == INTMINSTR) {
            temp = INT_MIN;
        } else {
            // INT_MIN is not handled correctly in following procedure
            if (nodestr[0] == '-') {
                sign = -1;
                ++i;
            } else if (nodestr[0] == '+') {
                ++i;
            }

            while (i < nodestr.size()) {
                temp = temp * 10 + nodestr[i] - '0';
                ++i;
            }
            temp = sign == 1 ? temp : -temp;
        }

        TreeNode* p = new TreeNode(temp);
        return p;
    }
};
class TreeUtil {
public:
    void printTree(TreeNode* root, string fill=".")
    {
        if (!root){
            return;
        }
        pair<int, int> wh = getWidthHeight(root);
        int R = wh.second;
        int C = wh.first;
        vector<vector<string> > result(R, vector<string>(C, fill));
        int r = 0;
        int c = (C - 1) / 2;
        print(result, root, r, c, C, R);
        for(vector<string>& v: result){
            for(string&s:v) {
                cout << s << " ";
            }
            cout << endl;
        }
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
#endif
