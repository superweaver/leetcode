#include "common.h"
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
		//root is not nullptr;
		int result = 0;
		int maxLevelSum = INT_MIN;

		queue<TreeNode*> q;
		q.push(root);
		int level = 1;
		while(!q.empty()) {
			size_t size = q.size();
			int currentLevelSum = 0;
			while(size--) {
				auto c = q.front();
				q.pop();
				currentLevelSum += c->val;	
				if(c->left) {
					q.push(c->left);
				}
				if(c->right) {
					q.push(c->right);
				}
			}
			// update
			if (currentLevelSum > maxLevelSum) {
				result = level;
				maxLevelSum = currentLevelSum;
			}
			// nextLevel
			level++;
		}
		return result;
    }
};

int main() {
	string str("1,7,0,7,-8,null,null");
	Codec codec;
	auto root = codec.deserialize(str);
	Solution s;
	cout << s.maxLevelSum(root) << endl;
	deleteTree(root);
	return 0;
}
