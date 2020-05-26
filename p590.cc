#include "common.h"
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
   	vector<int> postorder(Node* root) {
		if (!root) {
			return{};
		}
		vector<int> result;
		stack<Node*> s;
		Node* current = root;
		Node* pre = nullptr;
		while (current || !s.empty()) {
			while (current) {
				s.push(current);
				if (!current->children.empty()) {
					// don't push children[0]
					for (int i = current->children.size() - 1; i > 0; --i) {
						s.push(current->children[i]);
					}
					current = current->children[0];
				}
				else {
					current = nullptr;
				}
			}
			current = s.top();
			if (current->children.empty() || current->children.back() == pre) {
				// == 0 , leaf node
				s.pop();
				result.push_back(current->val);
				pre = current;
				current = nullptr;
			}
			else {
				// current->children is not empty();
				s.pop();
			}
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
