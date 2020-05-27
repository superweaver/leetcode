#include "common.h"
//https://www.cnblogs.com/grandyang/p/7200016.html
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int curMax = INT_MIN, n = nums.size();
        vector<int> idx(n, 0);
        auto cmp = [](pair<int, int>& a, pair<int, int>& b) {return a.first > b.first;};
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp) > q(cmp);
        for (int i = 0; i < n; ++i) {
            q.push({nums[i][0], i}); // value : row index
            idx[i] = 1;              // index in that row
            curMax = max(curMax, nums[i][0]);
        }
        vector<int> res{q.top().first, curMax};
        while (idx[q.top().second] < nums[q.top().second].size()) {
            // q's size will always be n;
            int t = q.top().second;
            q.pop();
            q.push({nums[t][idx[t]], t});
            curMax = max(curMax, nums[t][idx[t]]);
            ++idx[t];
            if (res[1] - res[0] > curMax - q.top().first) {
                res = {q.top().first, curMax};
            }
        }
        return res;
    }
};

int main() {

	Solution s;

	return 0;
}
