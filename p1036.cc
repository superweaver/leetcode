#include "common.h"
// https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
// https://blog.baozitraining.org/2019/05/leetcode-solution-1036-escape-large-maze.html
// https://www.acwing.com/solution/LeetCode/content/1695/
//
// assume there is m blocks, the max area it can cover is m*(m-1)/2 (form a triangle against wall)
// BFS, if source reach desination or we have seached more than m*(m-2)/2 squares, return true;
// do this for both source and destination
// if both true, then return true;
struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        std::size_t h1 = std::hash<T1>()(p.first);
        std::size_t h2 = std::hash<T1>()(p.second);
        return h1 ^ h2;
    }
};
class Solution
{
  public:
    bool isEscapePossible(vector<vector<int>> &blocked, vector<int> &source, vector<int> &target)
    {
        unordered_set<pair<int, int>, pair_hash> block;
        for (auto &p : blocked) {
            block.insert({p[0], p[1]});
        }
        pair<int, int> ps = {source[0], source[1]};
        pair<int, int> pt = {target[0], target[1]};
        return helper(block, ps, pt) && helper(block, pt, ps);
    }

  private:
    bool helper(unordered_set<pair<int, int>, pair_hash> &block, pair<int, int> s, pair<int, int> t)
    {
        int n = static_cast<int>(block.size());
        int upper = n * (n - 1) / 2;
        queue<pair<int, int>> q;
        q.push(s);
        unordered_set<pair<int, int>, pair_hash> visited;
        visited.insert(s);
        vector<int> dirs = {0, 1, 0, -1, 0};
        int searched = 0;
        while (!q.empty()) {
            auto c = q.front();
            q.pop();
            if (c == t) {
                return true;
            }
            for (int i = 0; i < 4; ++i) {
                int row = c.first + dirs[i];
                int col = c.second + dirs[i + 1];
                pair<int, int> p = {row, col};
                if (row < 0 || col < 0 || row >= 1000000 || col >= 1000000 || block.count(p) || visited.count(p)) {
                    continue;
                }
                visited.insert(p);
                searched++;
                q.push(p);
                if (searched > upper) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> blocked = {{0, 1}, {1, 0}};
    vector<int> source = {0, 0}, target = {0, 2};
	cout << s.isEscapePossible(blocked, source, target) << endl;
    return 0;
}
