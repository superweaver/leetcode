#include "common.h"
class Solution_ref {
public:
    int maxSumDivThree(vector<int>& nums) {

        int s = 0, min1 = INT_MAX, min2 = INT_MAX;

        for(auto n : nums) {
           s += n;

           if ( n % 3 == 1 ) {
               min2 = min1 == INT_MAX ? min2 : min(min2, min1 + n);
               min1 = min(min1, n);
           } else if ( n % 3 == 2 ) {
               min1 = min2 == INT_MAX ? min1 : min(min1, min2 + n);
               min2 = min(min2, n);
           }
        }

        if ( s % 3 == 0) return s;
        if ( s % 3 == 1) return s - min1;
        return s - min2;
    }
};

class Solution {
public:

    int maxSumDivThree(vector<int>& nums) {
		// my solution
		int sum = 0;
		// mod 3 == 0
		// mod 3 == 1
		// mod 3 == 2
        int mod2_m1 = INT_MAX - 1;
        int mod2_m2 = INT_MAX; 
		// two mod2 can make one mod1
        int mod1_m1 = INT_MAX-1;
		int mod1_m2 = INT_MAX;
		// two mod1 can make one mod2
		for(auto i : nums) {
			sum += i;
			if (i % 3 == 1) {
				if (i <= mod1_m1) {
					mod1_m2 = mod1_m1;
					mod1_m1 = i;
				}
				else if (i <= mod1_m2) {
					mod1_m2 = i;
				}
			} else if (i %3 == 2) {
                if (i <= mod2_m1) {
                    mod2_m2 = mod2_m1;
                    mod2_m1 = i;
                } else if (i <= mod2_m2) {
                    mod2_m2 = i;
                }
            }
        }
		if (sum %3 == 0) {
			return sum;
        } else if (sum % 3 == 1) {
			if (mod1_m1 == INT_MAX-1) { // no mod1, 1 is formed my two mod2
                return sum - mod2_m1 - mod2_m2;
            } else {
				// there is mod1_m1
				if (mod2_m1 == INT_MAX-1) { // no mod2
					return sum - mod1_m1;
				} else {
					// there is mod2
					if (mod2_m2 == INT_MAX) { // only mod2_m1
						return sum - mod1_m1;
					} else {
						return sum - min(mod1_m1, mod2_m1 + mod2_m2);
					}
				}
			}
        } else { // mod2
            if (mod2_m1 == INT_MAX - 1) {  // no mod2, 2 is formed my two mod1
                return sum - mod1_m1 - mod1_m2;
            } else {
                // there is mod2_m1
                if (mod1_m1 == INT_MAX - 1) {  // no mod1
                    return sum - mod2_m1;
                } else {
                    // there is mod1
                    if (mod1_m2 == INT_MAX) {  // only mod1_m1
                        return sum - mod2_m1;
                    } else {
                        return sum - min(mod2_m1, mod1_m1 + mod1_m2);
                    }
                }
            }
        }
    }
};
int main() {

    vector<int> nums = { 3, 6, 5, 1, 8 };
    nums = { 4 };
    nums = { 1, 2, 3, 4, 4 };
    nums = { 2, 6, 2, 2, 7 };
    Solution s;
    cout << s.maxSumDivThree(nums) << endl;
	return 0;
}
