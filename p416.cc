#include "common.h"
// not solved;
// dp and bitset solution
// http://www.cnblogs.com/grandyang/p/5951422.html
// backpack solution
// https://blog.csdn.net/liuyue910828/article/details/52792357
// https://blog.csdn.net/MebiuW/article/details/52765840
// f[i][j] is the max value we can get by putting the first i items into a pack with volumen of j
// f[i][j] = max(f[i-1][j], f[i-1][j-nums[i]] + nums[i]);

class Solution {
public:
    bool canPartition(vector<int>& nums) {
      int sum = 0;
        for(auto num: nums){
            sum += num;
        }
        if (sum&1) {
            return false;
        }
        bitset<5001> bits(1);// bit 0 = 1;
        for(auto num: nums){
            bits |= bits << num;
        }
        return bits[sum >> 1];
    }
};
class Solution_dp {
public:
    bool canPartition(vector<int>& nums) {
      int sum = 0;
        for(auto num: nums){
            sum += num;
        }
        if (sum&1) {
            return false;
        }
        int target = (sum >> 1);    // half of the sum
        vector<bool> dp(target + 1, false); // dp[i] means i can be constructed
        dp[0] = 1;
        // dp[i] = dp[i] || dp[i - nums[j]];  0 < nums[j] <= i <= target
        for (auto num : nums) {
         for(int i = target; i >= num; --i) {    // key !!!
                dp[i] = dp[i] || dp[i - num];
            }
        }
        return dp[target];
    }
};

int main() {

	Solution s;

	return 0;
}
