#include "common.h"
class Solution {
public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
		vector<int> count(n, 0);
		int total = 0;
		for (int i = 0; i < n; ++i) {
			int child = leftChild[i];
			if (child >= 0) {
				count[child]++;
				if (count[child] > 1) {
					return false;
				}
				total++;
			}
			child = rightChild[i];
            if (child >= 0) {
                count[child]++;
                if (count[child] > 1) {
                    return false;
                }
                total++;
            }
        }
		return total == n - 1;
    }
};

int main() {
    int n = 4;
	vector<int> leftChild = { 1, -1, 3, -1 };
	vector<int> rightChild = { 2, 3, -1, -1 }; // true
	n = 2, leftChild = {1,0}, rightChild = {-1,-1}; // false;
	n = 6, leftChild = {1,-1,-1,4,-1,-1}, rightChild = {2,-1,-1,5,-1,-1};// false;



    Solution s;
	cout << s.validateBinaryTreeNodes(n, leftChild, rightChild) << endl;

	return 0;
}
