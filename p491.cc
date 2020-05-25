#include "common.h"
// https://github.com/lzl124631x/LeetCode/tree/master/leetcode/491.%20Increasing%20Subsequences
class Solution {
private:
  vector<vector<int>> ans;
  void dfs(vector<int> &nums, int start, vector<int> &seq) {
    if (start == nums.size()) return;
    unordered_set<int> visited;
    for (int i = start; i < nums.size(); ++i) {
      int n = nums[i];
      if (visited.count(n) || (seq.size() && seq.back() > n)) continue;
      visited.insert(n);
      seq.push_back(n);
      if (seq.size() > 1) ans.push_back(seq);
      dfs(nums, i + 1, seq);
      seq.pop_back();
    }
  }
public:
  vector<vector<int>> findSubsequences(vector<int>& nums) {
    vector<int> seq;
    dfs(nums, 0, seq);
    return ans;
  }
};
//https://blog.csdn.net/magicbean2/article/details/78708889
/*
前缀生成法：注意到一个升序序列总是可以由升序的前缀加上当前整数组成，所以我们可以采用递推的方式由升序的前缀生成所有的结果。例如对于本题目，我们初始的升序前缀是{}，那么随着扫描的进行，结果的变化依次是：

当扫描到4之后，由升序前缀{{}}生成{4}，然后升序前缀更新为{{}, {4}}；

当扫描到6之后，由升序前缀{{}, {4}}生成{{6}, {4, 6}}，然后升序前缀更新为{{}, {4}, {6}, {4, 6}}；

当扫描到7之后，由升序前缀{{}, {4}, {6}, {4, 6}}生成{{7}, {4, 7}, {6, 7}, {4, 6, 7}}，然后升序前缀更新为{{}, {4}, {6}, {4, 6}, {7}, {4, 7}, {6, 7}, {4, 6, 7}}；

当再次扫描到7之后，由升序前缀{{}, {4}, {6}, {4, 6}, {7}, {4, 7}, {6, 7}, {4, 6, 7}}可以生成{{7}, {4, 7}, {6, 7}, {4, 6, 7}, {7, 7}, {4, 7, 7}, {6, 7, 7}, {4, 6, 7, 7}}，然后升序前缀更新为{{}, {4}, {6}, {4, 6}, {7}, {4, 7}, {6, 7}, {4, 6, 7}, {7}, {4, 7}, {6, 7}, {4, 6, 7}, {7, 7}, {4, 7, 7}, {6, 7, 7}, {4, 6, 7, 7}}。注意到背景为灰色的部分是重复元素，它们在set中将会被去重。最后再筛选出长度大于等于2的升序序列即可。
*/

class Solution_2 {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>> seqs = {vector<int>(0)};       // increasing prefix
         // note : this is not empty, it has one element which is empty vector.
        for (int i = 0; i < nums.size(); i++) {
            vector<vector<int>> built(seqs.size());     // get a copy of seqs
            std::copy(seqs.begin(), seqs.end(), built.begin());
            for (auto seq : built) {
                if (seq.empty() || nums[i] >= seq.back()) {
                    seq.push_back(nums[i]);
                    seqs.insert(seq);
                }
            }
        }
        vector<vector<int>> res;
        for (auto seq : seqs)
            if (seq.size() > 1) {
                res.push_back(seq);
            }
        return res;
    }
};



int main() {

	Solution s;

	return 0;
}
