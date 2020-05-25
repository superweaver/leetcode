#include "common.h"
// https://www.cnblogs.com/grandyang/p/6238425.html
/*
然后建立一个变量all，初始化为(1 << n) -
1，这是什么意思呢，all其实是一个mask，数组中有多少个数字，all就有多少个1，表示全选所有的数字，然后变量target表示一条边的长度。我们建立两个一位向量masks和validHalf，其中masks保存和target相等的几个数字位置的mask，validHalf保存某个mask是否是总和的一半。然后我们从0遍历到all，实际上就是遍历所有子数组，然后我们根据mask来计算出子数组的和，注意这里用了15，而不是32，因为题目中说了数组元素个数不会超过15个。我们算出的子数组之和如果等于一条边的长度target，我们遍历masks数组中其他等于target的子数组，如果两个mask相与不为0，说明有公用的数字，直接跳过；否则将两个mask或起来，说明我们当前选的数字之和为数组总和的一半，更新validHalf的对应位置，然后我们通过all取出所有剩下的数组，并在validHalf里查找，如果也为true，说明我们成功的找到了四条边
*/
class Solution {
  public:
    bool makesquare(vector<int> &nums) {
        // note: n <= 15
        if (nums.empty() || nums.size() < 4) {
            return false;
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4 != 0) {
            return false;
        }
        int n = nums.size();
        int target = sum / 4;
        int all = (1 << n) - 1;
        vector<int> masks;
        // for x in masks, the summation of elements from decomposition of x
        // is target
        vector<int> validHalf(1 << n, false);
        // for x in validHalf,  the summation of elements from decomposition of x (bit 1 of x)
        // is 2*target;
        for (int i = 0; i <= all; ++i) { // i is state
            int curSum = 0;
            // decomposition of state i
            for (int j = 0; j <= 15; ++j) {
                if ((i >> j) & 1) {
                    curSum += nums[j];
                }
            }

            if (curSum == target) {
                for (int mask : masks) {
                    if ((mask & i) != 0) {
                        continue; // has common element
                    }
                    // mask and i has no common element
                    // and then sum of decomposition of half is 2*target
                    int half = mask | i; // nice
                    validHalf[half] = true;
                    if (validHalf[all ^ half]) { // the other half;
                        return true;
                    }
                }
                // state i -> target
                masks.push_back(i);
            }
        }
        return false;
    }
};

class Solution_dfs {
  public:
    bool makesquare(vector<int> &nums) {
        if (nums.empty()) {
            return false;
        }
        // matchstick火柴棍
        sort(nums.begin(), nums.end(), greater<int>()); // ordered
        // reverse(nums.begin(), nums.end()); // larger in front
        int totalLen = 0;
        for (auto t : nums) {
            totalLen += t;
        }
        if (totalLen % 4) {
            return false;
        }
        int edgeLen = totalLen / 4;
        vector<int> edges(4, 0);
        return dfs(0, edgeLen, edges, nums);
    }

  private:
    bool dfs(size_t start, int targetlen, vector<int> &edges, vector<int> &nums) {
        if (start >= nums.size()) {
            for (size_t i = 0; i < edges.size(); ++i) {
                if (edges[i] != targetlen) {
                    return false;
                }
            }
            return true;
        }
        for (size_t i = 0; i < edges.size(); ++i) {
            if (edges[i] + nums[start] > targetlen) {
                // you can't put nums[start] in this edges[i]
                continue;
            }
            edges[i] += nums[start];
            if (dfs(start + 1, targetlen, edges, nums)) {
                return true;
            }
            edges[i] -= nums[start];
        }
        return false;
    }
};

int main() {

    Solution s;

    return 0;
}
