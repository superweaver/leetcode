#include "common.h"

class Solution_topologicalSort {

    bool dfs(int k, const vector<int>& a, vector<int>& color)
    {

        color[k] = 1; // visited, in loop , used in find loop in topological sort
        int next = (k + a[k]) % a.size();
        bool result = false;
        if (color[next] == 1 && next != k) { // self check
            result = true;
        }

        if (color[next] == 0 && a[next] > 0) {
            result = result || dfs(next, a, color);
        }

        color[k] = 2; // visited, not in loop
        return result;
    }

    bool check(const vector<int>& a)
    {
        vector<int> color(a.size(), 0); // unvisited
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] >= 0 && color[i] == 0) {
                if (dfs(i, a, color)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    bool circularArrayLoop(vector<int>& a)
    {
        int n = a.size();
        vector<int> b(n);
        for (int i = 0; i < n; ++i) {
            b[i] = -a[n - 1 - i];
        }
        return check(a) || check(b);
    }
};

class Solution_twopointer {
public:
    bool circularArrayLoop(vector<int>& nums) {
        if (nums.empty()) return false;
        int len = nums.size();
        int start = 0;
        // there should be a fast and slow pointer
        while (start < len) {
            if (getMod(nums[start], len) != 0) {
                int slow = start;
                int step = 0; // for slow
                int fast = start;
                int sign = nums[start] >= 0 ? 1 :-1;
                while (step < len) {
                    if (goonestep(fast, len, nums, sign)) {
                        if (goonestep(fast, len, nums, sign)) {

                        }
                        else {
                            break;
                        }
                    } else {
                        break;
                    }
                    if (goonestep(slow, len, nums, sign)) {
                        step++;
                    } else {
                        break;
                    }
                    if (fast == slow) {
                        return true;
                    }
                }
            }
            start++;
        }
        return false;
    }
private:
    int getMod(int a, int len) {
        // assume len >= 0;
        if (a >= 0) {
            return a % len;
        } else {
            int test = a % len;
            if (test > 0) {
                return test - len;
            } else {
                return test;
            }
        }
    }
    bool goonestep(int& start, int len, vector<int>& nums, int sign) {
        // check if you can go one step from index start
        // return false if you can't
        if (nums[start] * sign > 0) {
            int steps = getMod(nums[start], len);
            int next = start;
            if (steps > 0) {
                next = (next + steps)%len;
            } else if (steps < 0) {
                next = (next + len + steps) % len;
            } else {
                return false;
            }
            start = next;
            return true;
        }
        return false;
    }
};


int main() {


	return 0;
}
