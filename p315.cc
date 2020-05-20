#include "common.h"
// merge sort or BST
class Solution {
public:
    // merge sort !!
    vector<int> countSmaller(vector<int>& nums)
    {
        vector<int> result;
        int n = nums.size();
        if (n == 0) {
            return result;
        }
        vector<Node> copy;
        for (int i = 0; i < n; ++i) {
            Node node(nums[i], i);
            copy.push_back(node);
        }
        vector<Node> cache(copy);
        result = vector<int>(n, 0);
        mergeSort(copy, cache, 0, n - 1);
        for(auto& e: copy) {
            result[e.index] = e.smaller;
        }
        return result;
    }
    struct Node {
        int val;
        int smaller;
        int index;
        Node(int v, int i) : val(v), smaller(0), index(i) {}
    };

private:
    void mergeSort(vector<Node>& nums, vector<Node>& cache, int start, int end)
    {
        if (start >= end) {
            return;
        }
        int mid = start + (end - start) / 2;
        mergeSort(nums, cache, start, mid);
        mergeSort(nums, cache, mid + 1, end);
        int i = start;
        int j = mid + 1;
        int count = 0;
        for (; j <= end;) {
            if (nums[j].val < nums[i].val) {
                count++;
                j++;
            } else {
                // nums[i] >= nums[j]
                nums[i].smaller += count;
                i++;
                if (i > mid) {
                    break;
                }
            }
        }
        while (i <= mid) {
            nums[i].smaller += count;
            i++;
        }

        int index = start;
        i = start;
        j = mid + 1;
        while (i <= mid && j <= end) {
            if (nums[i].val <= nums[j].val) {
                cache[index] = nums[i];
                index++;
                i++;
            } else {
                cache[index] = nums[j];
                index++;
                j++;
            }
        }
        while (i <= mid) {
            cache[index] = nums[i];
            index++;
            i++;
        }
        while (j <= end) {
            cache[index] = nums[j];
            index++;
            j++;
        }

        for (index = start; index <= end; ++index) {
            nums[index] = cache[index];
        }
    }
};
//http://www.cnblogs.com/grandyang/p/5078490.html
// BST
//
class Solution_BST {
public:
	// BST with extra data member
   struct BSTNode {
		int val;
		int smaller;    // the number of smaller element on the right
		int count;
		BSTNode* left;
		BSTNode* right;
		BSTNode(int v) :val(v), smaller(0), count(1), left(nullptr), right(nullptr) {}
	};
	void deleteNode(BSTNode* root) {
		if (!root) return;
		deleteNode(root->left);
		deleteNode(root->right);
		delete root;
	}
	int insertNode(BSTNode*& root, int val) {
		if (!root) {
			root = new BSTNode(val);
			return root->smaller;
		}
		else {
			if (root->val < val) {
				int rightsmaller = insertNode(root->right, val);
				return root->smaller + root->count + rightsmaller;
			}
			else if (root->val == val) {
				++root->count;
				return root->smaller;
			}
			else {
				++root->smaller;
				return insertNode(root->left, val);
			}
		}

	}
	vector<int> countSmaller(vector<int>& nums) {
		vector<int> result(nums.size());
		BSTNode* root = nullptr;
		for (int i = nums.size() - 1; i >= 0; --i) {
			result[i] = insertNode(root, nums[i]);
		}
		deleteNode(root);
		return result;
	}
};


int main() {

	Solution s;

	return 0;
}
