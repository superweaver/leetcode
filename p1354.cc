#include "common.h"
class Solution {
public:
    bool isPossible(vector<int>& A) {
        long total = 0;
        int n = A.size(), a;
        priority_queue<int> pq(A.begin(), A.end());
        for (int a : A)
            total += a;
        while (true) {
            a = pq.top(); pq.pop();
            total -= a;
            if (a == 1 || total == 1)
                return true;
            if (a < total || total == 0 || a % total == 0)
                return false;
            a %= total;
            total += a;
            pq.push(a);
        }
    }
    /*
     * % operation is totally much more important than using heap.
If brute force solution is accepted,
then the solutions without % are right and good.

But the truth is that, solution without % should be TLE.
So I afraid that, without % is wrong to me.
     */
    bool isPossible_tle(vector<int>& target)
    {
        // https://leetcode.com/problems/construct-target-array-with-multiple-sums/discuss/510256/JavaC%2B%2BPython-Backtrack-OJ-is-wrong
        // https://leetcode.com/problems/construct-target-array-with-multiple-sums/discuss/510237/C%2B%2B-Priority-Queue-Simulate-Backwards-Accelerate-by-Module
        priority_queue<int> q(target.begin(), target.end());
        long long sum = 0;
        for (auto t : target) {
            sum += t;
        }
        int c = 0;
        while (true) {
            c = q.top();
            q.pop();
            sum -= c; // this is sum of others
            if (c == 1 || sum == 1) {
                // c == 1, then top is 1
                // it is true, not matter what sum is
                //
                // if sum == 1, that means [c, 1]
                // it is a special case
                return true;
            }
            if (c < sum || sum == 0 || c % sum == 0) {
                // c can't be smaller or equal to others
                // others can't be zero
                return false;
            }
            // note: if (c % sum == 0)
            // then no matter how many times of sum is applied
            // it is false
            // 
            // !!! % is the critical point
            c %= sum;
            sum += c;
            q.push(c);
        }
        // dummy
        return false;
    }
};

int main()
{
    vector<int> target = { 9, 3, 5 }; // 1
	target = {1,1,1,2}; // 0
    target = { 8, 5 }; // 1
    target = {1,1000000000};
    target = {2};

    Solution s;
	cout << s.isPossible(target) << endl;

	return 0;
}
