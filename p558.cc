#include "common.h"
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
class Solution {
  public:
    Node *intersect(Node *quadTree1, Node *quadTree2) {
        if (!quadTree1 || !quadTree2) {
            return nullptr;
        }
        if (quadTree1->isLeaf) {
            if (quadTree1->val) {
                return deepcopy(quadTree1);
            } else {
                return quadTree2;
            }
        }
        if (quadTree2->isLeaf) {
            if (quadTree2->val) {
                return quadTree2;
            } else {
                return quadTree1;
            }
        }

        Node *a = intersect(quadTree1->topLeft, quadTree2->topLeft);
        Node *b = intersect(quadTree1->topRight, quadTree2->topRight);
        Node *c = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
        Node *d = intersect(quadTree1->bottomRight, quadTree2->bottomRight);

        // key, merge when all child are Leaf and have same value
        // can't write as a->val == b->val == c->val == d->val :(, stupid mistake
        if (a->isLeaf && b->isLeaf && c->isLeaf && d->isLeaf && (a->val == b->val) &&
            (a->val == c->val) && (a->val == d->val)) {
            return new Node(a->val, true, nullptr, nullptr, nullptr, nullptr);
        } else {
            // if it is not a leaf node, its value must be false;
            // node's value can only be true when the node is leaf
            return new Node(false, false, a, b, c, d);
        }
    }

  private:
    Node *deepcopy(Node *root) {
        if (!root)
            return nullptr;
        Node *nr = new Node(root->val, root->isLeaf, nullptr, nullptr, nullptr, nullptr);
        nr->topLeft = deepcopy(root->topLeft);
        nr->topRight = deepcopy(root->topRight);
        nr->bottomLeft = deepcopy(root->bottomLeft);
        nr->bottomRight = deepcopy(root->bottomRight);
        return nr;
    }
};

int main() {

	Solution s;

	return 0;
}
