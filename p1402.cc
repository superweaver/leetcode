#include "common.h"
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
		sort(satisfaction.begin(), satisfaction.end());
		if (satisfaction.back() <= 0) {
			return 0;
		}
		int n = satisfaction.size();
        vector<int> suffix_sum(n + 1, 0);
		int r = 0;
        for (int i = n - 1; i >= 0; --i) {
            suffix_sum[i] = suffix_sum[i+1] + satisfaction[i];
			r += suffix_sum[i];	
        }
		//int r = accumulate(suffix_sum.begin(), suffix_sum.end(), 0);
        int result = r;
        for (int i = 1; i < n; ++i) {
            if (satisfaction[i] >= 0) {
                break;
            }
            r -= suffix_sum[i - 1];
            result = max(result, r);
        }
        return result;
    }
};

int main() {

	vector<int> satisfaction = {-1,-8,0,5,-9}; // 14
	satisfaction = {-2,5,-1,0,3,-3}; // 35
	Solution s;
	cout << s.maxSatisfaction(satisfaction) << endl;

	return 0;
}
