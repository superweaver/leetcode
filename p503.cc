#include "common.h"

class Solution {
    // https://leetcode.com/problems/next-greater-element-ii/discuss/98273/Java-10-lines-and-C%2B%2B-12-lines-linear-time-complexity-O(n)-with-explanation
    // https://leetcode.com/problems/next-greater-element-i/discuss/97595/java-10-lines-linear-time-complexity-on-with-explanation
    public:
    vector<int> nextGreaterElements(vector<int> &nums) {
        int n = nums.size();
        vector<int> next(n, -1);
        stack<int> s; // index stack
        // at most 2 * n;
        for (int i = 0; i < n * 2; i++) {
            int num = nums[i % n];
            while (!s.empty() && nums[s.top()] < num) {
                next[s.top()] = num;
                s.pop();
            }
            // key point
            if (i < n) {
                s.push(i);
            }
        }
        return next;
    }
};

class Solution_my {
public:
	vector<int> nextGreaterElements(vector<int>& nums) {
		// use stack to store index
		vector<int> result;
		if (nums.empty()) {
			return result;
		}
		int n = nums.size();
		if (n == 1) {
			return { -1 };
		}
		result = vector<int>(n, -1);
		vector<int> s;// act as stack to store index
		int next = 0;
		int found = 0;
		while (found < n) {
            // next = next % n;
			if (next >= n) {
				next -= n;
			}

			if (s.empty()) {
                if (result[next] != -1) {
                    // skip it
                    next++;
                    continue;
                } else {
                    s.push_back(next);
                    next++;
                }
            }
			else {
				// it is possible all the remaining elements in s are the maximum value
				if (next == s.front() && nums[s.front()] == nums[s.back()]) {
					break;
				}
				// check if nums[next] > stack.back()
                if (nums[next] <= nums[s.back()]) {
                    if (result[next] != -1) {
                        // skip it
                        next++;
                        continue;
                    } else {
                        s.push_back(next);
                        next++;
                    }
                } else {
                    // found one
                    result[s.back()] = nums[next];
                    found++;
                    s.pop_back();
                }
            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
