#include "common.h"
class Solution {
	// avoid copy
public:
    int maxSumBST(TreeNode* root) {
		// return [min, max, isBST, sum]
        if (!root) {
            return 0;
        }
		int result = 0; // empty BST's sum is zero!!!
		int minv = INT_MAX;
		int maxv = INT_MIN;
		int sum = 0;
        helper(root, minv, maxv, sum, result);
        return result;
    }
private:
    bool helper(TreeNode* root, int& minv, int& maxv, int& sum, int& result)
    {
        if(!root) {
			return true;
		}
        int lminv = INT_MAX;
        int lmaxv = INT_MIN;
        int lsum = 0;
		bool l = true;
        if (root->left) {
            l = helper(root->left, lminv, lmaxv, lsum, result);
		}
        int rminv = INT_MAX;
        int rmaxv = INT_MIN;
        int rsum = 0;
		bool r = true;
		if (root->right) {
            r = helper(root->right, rminv, rmaxv, rsum, result);
        }
		sum = lsum + rsum + root->val;
        minv = min(root->val, min(lminv, rminv));
		maxv = max(root->val, max(lmaxv, rmaxv));
		bool isBST = false;
        if (l && r && lmaxv < root->val && root->val < rminv) {
			isBST = true;	
			result = max(result, sum);
		}
		return isBST;
    }
};

class Solution_copy {
public:
    int maxSumBST(TreeNode* root) {
		// return [min, max, isBST, sum]
        if (!root) {
            return 0;
        }
		int result = 0; // empty BST's sum is zero!!!
		helper(root, result);
        return result;
    }
private:
	vector<int> helper(TreeNode* root, int& result) {
		if(!root) {
			return {INT_MAX, INT_MIN, 1, 0};
		}
		auto l = helper(root->left, result);
		auto r = helper(root->right, result);
		int sum = l[3] + r[3] + root->val;
        int minv = min(root->val, min(l[0], r[0]));
		int maxv = max(root->val, max(l[1], r[1]));
		int isBST = 0;
        if (l[2] && r[2] && l[1] < root->val && root->val < r[0]) {
			isBST = 1;	
			result = max(result, sum);
		}
		return {minv, maxv, isBST, sum};
	}
};

int main() {
	string str = "1,4,3,2,4,2,5,null,null,null,null,null,null,4,6"; // 20
	//str = "4,3,null,1,2"; // 2
	str = "-4,-2,-5"; // 0, empty BST
    str = "2,1,3";
    str = "5,4,8,3,null,6,3";
    Codec codec;
	auto root = codec.deserialize(str);
	Solution s;
	cout << s.maxSumBST(root) << endl;
	deleteTree(root);
	return 0;
}
