#include "common.h"
// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/discuss/335668/DP-with-Bit-Masking-Solution-%3A-Best-for-Interviews
//
//
//
// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/discuss/140541/Clear-explanation-easy-to-understand-C%2B%2B-%3A-4ms-beat-100
// Put n items into k bucket so each bucket has same total item value.

//    For each bucket, try all possible content O(k*2^n) -- no good.
 //   For each item, try all possible destined bucket O(k^n) -- doable.

class Solution {
  public:
    // use global variables to avoid long parameter list
    int target; // of each bucket
    vector<int> ns;
    vector<int> bucket;

    bool canPartitionKSubsets(vector<int> &nums, int k) {
        int sum = 0;
        for (int &n : nums) {
            sum += n;
        }
        if (sum % k) {
            return false; // not divisible
        }
        target = sum / k;
        ns = vector<int>(nums);
        bucket = vector<int>(k, 0); // k buckets

        // starting with bigger ones makes it faster
        sort(ns.begin(), ns.end());
        reverse(ns.begin(), ns.end());
        return put(0);
    }

    // put #n item of ns into some bucket to meet target
    bool put(int n) {
        for (int i = 0; i < bucket.size(); ++i) {
            if (bucket[i] + ns[n] > target) {
                continue;       // try next bucket
            }
            bucket[i] += ns[n]; // put it in!
            if (n == ns.size() - 1) {
                return true; // all items in bucket, no overflow
            }
            if (put(n + 1)) {
                return true;        // move on to next item
            } else {                // no solution = wrong bucket
                bucket[i] -= ns[n]; // take it out
                /// !!!!
                if (bucket[i] == 0) { 
                    // ??? no solution, after taking it out, it means we failed to find a bucket
                    // for current #n item
                    // if bucket[i] == 0, and then all the remaining buckets are all 0, no solution for them too
                    // then no solution
                    return false; // no need to try other empty bucket
                }
            }
        }
        return false; // no bucket fits
    }
};

class Solution_my {
  public:
    bool canPartitionKSubsets(vector<int> &nums, int k) {
        if (nums.empty())
            return false; // need non-empty subarray
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k)
            return false;
        int target = total / k;
        sort(nums.begin(), nums.end());
        if (nums.back() > target)
            return false;
        while (nums.back() == target) {
            nums.pop_back();
            k--;
        }

        vector<bool> visited(nums.size(), false);
        return helper(nums, target, 0, nums.size() - 1, visited, k);
    }

  private:
    bool helper(vector<int> &nums, const int &target, int currentSum, int end,
                vector<bool> &visited, int groups) {
        if (currentSum > target)
            return false;
        if (currentSum == target) {
            groups--;
            if (groups == 0) {
                return true;
            } else {
                // continue;
                return helper(nums, target, 0, nums.size() - 1, visited, groups);
            }
        } else {
            // find biggest one in the nums
            for (int i = end; i >= 0; --i) {
                if (visited[i] == false) {
                    visited[i] = true;
                    if (helper(nums, target, currentSum + nums[i], i - 1, visited, groups)) {
                        return true;
                    }
                    visited[i] = false;
                } else {
                    continue;
                }
            }
            return false;
        }
    }
};

int main() {

    Solution s;

    return 0;
}
