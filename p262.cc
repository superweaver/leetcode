#include "common.h"

class Solution {
public:

    int nthUglyNumber_set(int n) {
        set<int> cache;
        cache.insert(1);

        //priority_queue<int, vector<int>, greater<int>> q;// multiple redundants
        // can't work
        //q.push(1);
        vector<int> ugly;
        while (ugly.size() < n) {
            auto v = *cache.begin();
            ugly.push_back(v);
            cache.erase(cache.begin());
            cache.insert(2 * v);
            cache.insert(3 * v);
            cache.insert(5 * v);
            /*
            auto v = q.top();
            ugly.push_back(v);
            q.pop();
            q.push(2*v);
            q.push(3*v);
            q.push(5*v);
            */
        }
        return ugly.back();
    }
    int nthUglyNumber(int n) {
        // not solved
        // https://www.geeksforgeeks.org/ugly-numbers/
        //
        // k = min(2 * dp[i2] , 3 * dp[i3], 5* dp[i5]);
        // i2, i3, i5 goes through 0, 1, 2, ...
        // each generators goes through from head of dp list
        // times them with 2 or 3, or 5
        vector<int> ugly(n, 1);
        ugly[0] = 1;
        int i2 = 0, i3 = 0, i5 = 0;
        int next_multiple_of_two = 2 * ugly[i2];    // generators
        int next_multiple_of_three = 3 * ugly[i3];
        int next_multiple_of_five = 5 * ugly[i5];

        for (int i = 1; i < n; ++i) {
            // next ugly number will only come from next_multiple_of_two , next_multiple_of_two, next_multiple_of_five
            int next = min(next_multiple_of_two, min(next_multiple_of_three, next_multiple_of_five));
            ugly[i] = next; // fill first.
            if (next == next_multiple_of_two) {
                ++i2;   // this is the key. point to next element to array. which has already been filled.
                next_multiple_of_two = 2 * ugly[i2];
            }
            if (next == next_multiple_of_three) {
                ++i3;
                next_multiple_of_three = 3 * ugly[i3];
            }
            if (next == next_multiple_of_five) {
                ++i5;
                next_multiple_of_five = 5 * ugly[i5];
            }
        }
        return ugly[n-1];
    }
};

int main() {
    int n = 100;
	Solution s;
    cout << s.nthUglyNumber(n) << endl;
    cout << s.nthUglyNumber_set(n) << endl;

	return 0;
}
