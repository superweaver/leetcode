#include "common.h"
class Solution {
public:
	int pathSum(TreeNode* root, int sum) {
		if (!root) return 0;
		unordered_map<int, int> accumulateSum; // sum -> count in previous path
		accumulateSum[0] = 1;	 // key
		int result = 0;
		dfs(root, sum, 0, result, accumulateSum);
		return result;
	}
private:
	void dfs(TreeNode* root, int target, int pathSum, int& result, unordered_map<int, int>& cache) {
		if (!root) return;
		pathSum += root->val;
		// key
		if (cache.find(pathSum - target) != cache.end()) {
			result += cache[pathSum - target];
		}
		cache[pathSum]++;    // it is possible that pathSum is 0 now !!!
		dfs(root->left, target, pathSum, result, cache);
		dfs(root->right, target, pathSum, result, cache);
		cache[pathSum]--;
	}
};

int main() {

	Solution s;

	return 0;
}
