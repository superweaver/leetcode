#include "common.h"
class Solution {
public:
    int minInsertions(string s)
    {
        // 1 <= s.length <= 500
        int n = s.size();
        vector<vector<int>> cache(n, vector<int>(n, -1));
        return helper(0, n - 1, s, cache);
    }

private:
    int helper(int start, int end, string& s, vector<vector<int>>& cache)
    {
        if (start > end) {
            return 0;
        }
        if (cache[start][end] >= 0) {
            return cache[start][end];
        }
        if (start == end) {
            return cache[start][end] = 0;
        }
        if (s[start] == s[end]) {
            return cache[start][end] = helper(start + 1, end - 1, s, cache);
        } else {
            return cache[start][end] = min(1 + helper(start + 1, end, s, cache),
                                           1 + helper(start, end - 1, s, cache));
        }
        return 0;
    }
};

int main()
{
    string s = "zzazz"; // 0
	s = "mbadm"; // 2
	s = "leetcode"; // 5
	s = "g"; // 0
	s = "no"; // 1
    Solution so;
	cout << so.minInsertions(s) << endl;
    return 0;
}
