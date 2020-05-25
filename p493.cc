#include "common.h"
// nice summary !!!
// https://leetcode.com/problems/reverse-pairs/discuss/97268/General-principles-behind-problems-similar-to-%22Reverse-Pairs%22
// author  fun4LeetCode 
class Solution {
public:
    int reversePairs(vector<int>& nums) {
       // merge sort
       if (nums.size() < 2) return 0;
       return mergesort(nums, 0, nums.size());
    }
private:
    int mergesort(vector<int>&nums, int begin, int end) {
        // begin is inclusive, end is exclusive
        int len = end - begin;
        if (len < 2) return 0;
        if (len == 2) {
            int count = nums[begin] > ((long long)nums[begin + 1] * 2);
            if (nums[begin] > nums[begin + 1]) {
                swap(nums[begin], nums[begin + 1]);
            }
            return count;
        }
        int mid = begin + len / 2;
        int leftlen = mid - begin;
        int rightlen = len -leftlen;
        int l = mergesort(nums, begin, mid);
        int r = mergesort(nums, mid, end);
        // merge and count
        int count = 0;
        vector<int> left(leftlen, 0);
        for (int i = begin, j = 0; i < mid; i++) {
            left[j++] = nums[i];
        }
        vector<int> right(rightlen, 0);
        for (int i = mid, j = 0; i < end; ++i) {
            right[j++] = nums[i];
        }
        vector<int> next(len, 0);
        int p_left = 0;
        int p_right = 0;
        int p_next = 0;
        // count only
        while (p_left < leftlen && p_right < rightlen) {
            // avoid overflow
            if (left[p_left] <= ((long long)right[p_right] * 2)) {
            //if (left[p_left] - right[p_right] <= right[p_right]) {
                p_left++;
            } else {
                p_right++;
                count += (leftlen - p_left);
            }
        }
        // real merge
        p_left = p_right = p_next = 0;
        while (p_left < leftlen && p_right < rightlen) {
            if (left[p_left] <=  right[p_right]) {
                next[p_next++] = left[p_left++];
            } else {
                next[p_next++] = right[p_right++];
            }
        }
        while(p_left < leftlen) {
            next[p_next++] = left[p_left++];
        }
        while(p_right < rightlen) {
            next[p_next++] = right[p_right++];
        }
        for (int i = begin, j = 0; i < end; ++i) {
            nums[i] = next[j++];
        }
        return l + r + count;
    }
};

int main() {

	Solution s;

	return 0;
}
