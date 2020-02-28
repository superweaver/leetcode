#include "common.h"
class FindElements {
public:
    FindElements(TreeNode* root) {
		this->root = root;
    }

    bool find(int target) {
		vector<int> path;
		if (!target) {
			return true;
		}
		while(target) {
			path.push_back(target);	
			target = (target - 1) / 2;
		}	
		path.push_back(0);
		int n = path.size();
		TreeNode* pre_node = root;
		for (int j = n - 2; j >= 0; --j) {
            if (path[j] == (2 * path[j + 1] + 1)) {
                if (pre_node->left == nullptr) {
					return false;
				} else {
					pre_node = pre_node->left;
				}
            } else {
                if (pre_node->right == nullptr) {
					return false;
				} else {
					pre_node = pre_node->right;
				}
            }
        }
		return true;
    }
private:
	TreeNode* root;
	//unordered_map<int, TreeNode*> trees;
};
int main() {

	Solution s;

	return 0;
}
