#include "common.h"
// https://leetcode.com/problems/design-skiplist/discuss/400028/C%2B%2B-SkipList.-2-pointer-for-each-node.-64ms.
//
struct Node {
    Node *right; // point to right of current level
    Node *down;  // point to Node of down level
    int val;
    Node(Node *right, Node *down, int val) : right(right), down(down), val(val) {}
};

class Skiplist {
    Node *head;

  public:
    Skiplist() { head = new Node(NULL, NULL, 0); }
    ~Skiplist() { delete head; }

    bool search(int num) {
        Node *p = head;
        while (p) {
            while (p->right && p->right->val < num) {
                p = p->right;
            }
            if (!p->right || p->right->val > num) {
                p = p->down;
            } else {
                // p->right && p->right->val == num;
                return true;
            }
        }
        return false;
    }

    void add(int num) {
        vector<Node *> insertPoints;
        Node *p = head;
        // top down
        while (p) {
            while (p->right && p->right->val < num) {
                p = p->right;
            }
            insertPoints.push_back(p);
            p = p->down;
        }

        Node *downNode = NULL; // point to Node of lower layer

        bool insertUp = true; // stop or continue
        // bottom up
        while (insertUp and insertPoints.size()) {
            Node *ins = insertPoints.back();
            insertPoints.pop_back();

            // create node of same value multiple times
            ins->right = new Node(ins->right, downNode, num);
            downNode = ins->right;

            insertUp = (rand() & 1) == 0;
        }

        if (insertUp) {
            // need to introduce a new layer
            // need a new node and a new head
            // head->right = new Node(NULL, downNode, num)
            head = new Node(new Node(NULL, downNode, num), head, 0);
        }
    }

    bool erase(int num) {
        Node *p = head;
        bool seen = false;
        while (p) {
            while (p->right && p->right->val < num) {
                p = p->right;
            }
            if (!p->right || p->right->val > num) {
                p = p->down;
            } else {
                seen = true;
                auto remove = p->right;
                p->right = p->right->right;
                delete remove;
                p = p->down;
            }
        }
        return seen;
    }
};

int main() {
    Skiplist skiplist;
    skiplist.add(1);
    skiplist.add(2);
    skiplist.add(3);
    skiplist.search(0); // return false.
    skiplist.add(4);
    skiplist.search(1); // return true.
    skiplist.erase(0);  // return false, 0 is not in skiplist.
    skiplist.erase(1);  // return true.
    skiplist.search(1); // return false, 1 has already been erased.

    return 0;
}
