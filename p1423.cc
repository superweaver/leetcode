#include "common.h"
class Solution {
public:

    int maxScore(vector<int>& cardPoints, int k) {
		int n = cardPoints.size();
		int left = 0;
        for (int i = 0; i < k; ++i) {
            left += cardPoints[i];
        }
        int result = left;
		if(n == k) {
			return result;
        }

		int i = k - 1;
		while(i >= 0)
		{
			left -= cardPoints[i];
			//left += cardPoints[n - 1 - (k - 1 - i)];
			left += cardPoints[n - k + i];
			result = max(result, left);
            i--;
		}
		return result;
    }

    int maxScore2(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
		if(k * 2 + 2 < n + 1)
		{
			vector<int> left_sum(k + 1, 0);
			for(int i = 0; i < k; ++i)
			{
				left_sum[i + 1] = left_sum[i] + cardPoints[i];
			}

			vector<int> right_sum(k + 1, 0);
			for(int i = 0; i < k; ++i)
			{
				right_sum[i + 1] = right_sum[i] + cardPoints[n - 1 - i];
			}

			int result = INT_MIN;
			for(int leftlen = 0; leftlen <= k; ++leftlen)
			{
				// rightlen = k - leftlen;
				result = max(result, left_sum[leftlen] + right_sum[k - leftlen]);
			}
			return result;
		}
        else {
			vector<int> left_sum(n + 1, 0);
			for(int i = 0; i < n; ++i)
			{
				left_sum[i + 1] = left_sum[i] + cardPoints[i];
			}
			int result = INT_MIN;
			for(int leftlen = 0; leftlen <= k; ++leftlen)
			{
				// rightlen = k - leftlen;
				result = max(result, left_sum[leftlen] + left_sum[n] - left_sum[n - k + leftlen]);
			}
			return result;
		}
	}
};

int main() {

    vector<int> cardPoints = {1,2,3,4,5,6,1};
    int k = 3; // 12
//	cardPoints = {2, 2, 2}, k = 2; // 4
//	cardPoints = {9, 7, 7, 9, 7, 7, 9}, k = 7; // 55
    //cardPoints = {1,1000,1}, k = 1; // 1
    //cardPoints = {1,79,80,1,1,1,200,1}, k = 3; // 202



	Solution s;
    cout << s.maxScore(cardPoints, k) << endl;
	return 0;
}
