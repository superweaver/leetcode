#include "common.h"

class Solution_ref {
public:
    int superpalindromesInRange(string L, string R) {
        long double lb = sqrtl(stol(L)), ub = sqrtl(stol(R));
        int ans = lb <= 3 && 3 <= ub;
        queue<pair<long, int>> q;
        q.push({1, 1}), q.push({2, 1});
        while (true) {
            auto p = q.front(); q.pop();
            long x = p.first, len = p.second;
            if (x > ub) break;
            long W = powl(10, (len + 1) / 2);
            if (x >= lb) {
                ans += is_palindrome(x * x);
            }
            long r = x % W, l = x - (len % 2 ? x % (W / 10) : r);
            if (len % 2) {
                q.push({10 * l + r, len + 1});
            } else {
                for (int d = 0; d <= 2; d++) {
                    q.push({10 * l + d * W + r, len + 1});
                }
            }
        }
        return ans;
    }
private:
    bool is_palindrome(long x) {
        if (x == 0) return true;
        if (x % 10 == 0) return false;
        long left = x, right = 0;
        while (left >= right) {
            if (left == right || left / 10 == right) return true;
            right = 10 * right + (left % 10), left /= 10;
        }
        return false;
    }
};

class Solution {
// https://www.cnblogs.com/grandyang/p/11204481.html
public:
    // 1 <= len(L) <= 18
    // 0 <= stol(L) < 1e18
    int superpalindromesInRange(string L, string R)
    {
        long left = stol(L);
        long right = stol(R);
        int result = 0;
        helper("", left, right, result);
        for(char c = '0'; c <= '9'; ++c) {
            helper(string(1, c), left, right, result);
        }
        return result;
    }
    private :
    void helper(string current, long left, long right, int& result) {
        if(current.size() > 9) {
            return;
        }
        if(!current.empty() && current[0] != 0) {
            long v = stol(current);
            v *= v;
            if(v > right) {
                return;
            } else if (v >= left && isPalindrome(to_string(v))) {
                result++;
            } // else { // expand in two ends }
        }
        for(char c = '0'; c <= '9'; ++c) {
            helper(string(1, c) + current + string(1, c), left, right, result);
        }
    }
    bool isPalindrome(const string& s)
    {
        if (s.empty()) {
            return false;
        }
        int i = 0, j = s.size() - 1;
        while (i < j) {
            if (s[i++] != s[j--]) {
                return false;
            }
        }
        return true;
    }
};


int main() {

	Solution_ref s;
    cout << s.superpalindromesInRange("4", "1000") << endl;

	return 0;
}
