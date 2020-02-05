#include "common.h"
class Solution {
	// https://zhanghuimeng.github.io/post/leetcode-968-binary-tree-cameras/
	// https://www.charliechen.cn/en/leetcode-968-binary-tree-cameras/
public:
	int minCameraCover(TreeNode* root) {
		if (!root) return 0;
		// each node must be in one of three state
		// state 0 : covered by at least one of its child
		// state 1 : install a camera on root
		// state 2 : covered by its parents
		// dp[0], dp[1], dp[2] means the min carema for root with its final state in 0, 1, and 2
		// dp[0] = min(l[1] + min(r[0], r[1]), r[1] + min(l[0], l[1]));            
		// dp[1] = 1 + min(min(l[0], l[1]),l[2]) + min(min(r[0], r[1]),r[2]);
		// dp[2] = sum(min(l[0],l[1]) , min(r[0], r[1]));
		auto p = helper_dp(root);	
		return (p[0] == -1) ? p[1] : min(p[0], p[1]);
		
	}
	vector<int> helper_dp(TreeNode* root) {
		if (!root->left && !root->right) {
			return {-1, 1, 0};
		}
		if (root->left && !root->right) {
			auto l = helper_dp(root->left);
			int dp0 = (l[1] == -1) ? -1 : l[1];	
			int lmin01 = (l[0] == -1) ? l[1] : min(l[0], l[1]);
			int dp1 = 1 + ((l[2] == -1) ? lmin01 : min(lmin01, l[2])); 
			int dp2 = lmin01;
			return {dp0, dp1, dp2};
		}
		if (root->right && !root->left) {
			auto r = helper_dp(root->right);
			int dp0 = (r[1] == -1) ? -1 : r[1];	
			int rmin01 = (r[0] == -1) ? r[1] : min(r[0], r[1]);
			int dp1 = 1 + ((r[2] == -1) ? rmin01 : min(rmin01, r[2])); 
			int dp2 = rmin01;
			return {dp0, dp1, dp2};
		}
		auto l = helper_dp(root->left);
		auto r = helper_dp(root->right);
		int lmin01 = (l[0] == -1) ? l[1] : min(l[0], l[1]);
		int rmin01 = (r[0] == -1) ? r[1] : min(r[0], r[1]);
		int dp0 = min(l[1] + rmin01, r[1] + lmin01);
		int dp1 = 1 + ((l[2] == -1) ? lmin01 : min(lmin01, l[2])) + ((r[2] == -1) ? rmin01 : min(rmin01, r[2])); 
		int dp2 = (lmin01 +  rmin01);
		return {dp0, dp1, dp2};
	}
    int minCameraCover_greedy(TreeNode* root) {
		// greedy
		if (!root) {
			return 0;
		}
		int result = 0;
		auto p = helper_greedy(root, result);
		return result + ((p == 0) ? 1 : 0);
    }
	private:
	int helper_greedy (TreeNode* root, int& result) {
		// 0 = not covered
		// 1 = put camera on root
		// 2 = no camera on root but covered by others' camera
		if (!root->left && !root->right) {
			// greedy
			return root->val = 0;
		}
		bool putCamera = false;
		bool coveredByOther = false;
		if (root->left) {
			int s = helper_greedy(root->left, result);
			if (s == 0) {
				// put carema at root
				putCamera = true;
			}
			if (s == 1) {
				coveredByOther = true;
			}
		}
		if (root->right) {
			int s = helper_greedy(root->right, result);
			if (s == 0) {
				// put carema at root
				putCamera = true;
			}
			if (s == 1) {
				coveredByOther = true;
			}
		}

		if (putCamera) {
			result++;
			return root->val = 1;
		}

		if (coveredByOther) {
			return root->val = 2;
		} else {
			return 0;
		}
	}
};
int main() {

	string t = "0,0,null,0,0"; // 1
	t = "0,0,null,0,null,0,null,null,0";
	t = "0";
	t = "0,0,null,0,0,0,null,null,0";
	Codec codec;
	auto root = codec.deserialize(t);
	TreeUtil tu;
	tu.printTree(root);
	Solution s;
	cout << s.minCameraCover(root) << endl;
	cout << s.minCameraCover_greedy(root) << endl;
	deleteTree(root);
	return 0;
}
