#include "common.h"

class Solution {
public:
	// optionally delete one element :( !!!!
	// you can choose delete or not delete
    int maximumSum(vector<int>& a)
    {

        int ans = a[0];
        int prefixMxSum = a[0]; 
		// prefixMxSum[i] is the max prefix sum without deletion up to index i;
        int prefixMxSumDel = 0; // prefix max sum with deletion one element
		// prefixMxSumDel[i] is the max prefix sum with one deletion, up to index i;
		// note: 
		// prefixMxSumDel[i] = one of following case
		// 1) delete a[i], then this is equivalent to prefixMxSum[i-1];
		// 2) attach a[i] to prefixMxSumDel[i-1]; the deletion point is before a[i];
		// ans = max(prefixMxSum, prefixMxSumDel)
        int sz = a.size();
        for (int i = 1; i < sz; i++) {
            prefixMxSumDel = max(prefixMxSumDel + a[i], prefixMxSum); // !!!! 
			// note here, prefixMxSum is equivalent to delete node a[i];
			// while prefixMxSumDel means there is one deletion previously
            prefixMxSum = max(prefixMxSum + a[i], a[i]); // nice
            ans = max(ans, max(prefixMxSum, prefixMxSumDel));
        }
        return ans;
    }

    int maximumSum_my(vector<int>& arr) {
		// my solution
		arr.push_back(0);
		int n = arr.size();
		int pre = 0;
		int temp = 0;
		int maxElement = INT_MIN;
		for (int i = 0; i < n - 1; ++i) {
			maxElement = max(maxElement, arr[i]);
            temp = arr[i];
			arr[i] = pre;
			pre += temp;
		}
		if (maxElement <= 0) {
			return maxElement;
		}
        arr[n - 1] = pre;
		// pre is the total sum;
		vector<int> right(arr);
		int high = right[n-1];

		for (int i = n - 2; i >= 0; --i) {
            //	i is the delete point
			right[i] = 	max(high - arr[i + 1], 0);
			// update high
			high = max(high, arr[i + 1]);
        }
		int result = INT_MIN;
		int low = arr[0];
		for (int i = 0; i < n - 1; ++i) {
			result = max(result, right[i] + max(arr[i] - low, 0));
			low = min(low, arr[i]);
		}
		/*
		vector<int> left(arr);
		int low = arr[0];

		for (int i = 0; i < n - 1; ++i) {
			left[i] = arr[i] - low;	
			low = min(low, arr[i]);
		}

		int result = INT_MIN;
		for (int i = 0; i < n - 1; ++i) {
			result = max(result, left[i] + right[i]);
		}
		*/
		return result;

    }
};

int main() {
    vector<int> arr = { 1, -2, 0, 3 };
	arr = {1,-2,-2,3};
	arr = {-1,-1,-1,-1};
    Solution s;
	cout << s.maximumSum(arr) << endl;
	return 0;
}
