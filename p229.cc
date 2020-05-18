#include "common.h"
//https://gregable.com/2013/10/majority-vote-algorithm-find-majority.html
class Solution {
  public:
    vector<int> majorityElement(vector<int> &nums) {
        // not solved.
        // need to decide if nums has such major element
        // http://www.cnblogs.com/grandyang/p/4606822.html
        /*
            需要两遍遍历，第一遍历找出两个候选众数，第二遍遍历重新投票验证这两个候选众数是否为众数即可，
            选候选众数方法和前面那篇Majority Element
           求众数一样，由于之前那题题目中限定了一定会有众数存在
            ，故而省略了验证候选众数的步骤，这道题却没有这种限定，即满足要求的众数可能不存在，所以要有验证。
        */
        vector<int> result;
        // at most 2 major elements
        int m1 = 0;
        int count_m1 = 0;
        int m2 = 0;
        int count_m2 = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] == m1) {
                ++count_m1;
            } else if (nums[i] == m2) {
                ++count_m2;
            } else if (count_m1 == 0) {
                m1 = nums[i];
                count_m1 = 1;
            } else if (count_m2 == 0) {
                m2 = nums[i];
                count_m2 = 1;
            } else {
                --count_m1;
                --count_m2;
            }
        }
        // check if m1 and m2 are valid
        // count only
        count_m1 = count_m2 = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] == m1) {
                ++count_m1;
            } else if (nums[i] == m2) {
                ++count_m2;
            }
        }
        if (count_m1 > (nums.size() / 3)) {
            result.push_back(m1);
        }
        if (count_m2 > (nums.size() / 3)) {
            result.push_back(m2);
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
