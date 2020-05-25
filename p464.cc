#include "common.h"
class Solution {
//https://www.cnblogs.com/grandyang/p/6103525.html
public:
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if (maxChoosableInteger >= desiredTotal) {
			// can get it in the first run
			return true;
		}
		// overflow ?
		if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) {
			// impossible to get desiredTotal
			return false;
		}

		// maxChoosableInteger <= 20
		int flag = 0; // bit i of flag == 1 means int (i+1) has been visited
		unordered_map<int, bool> cache; // can you win with curret visit status flag
        // flag determine if you can win or you will definitely lose
        // you can win if there is a path to go to a state where other is defintely lose
        // cache[flag] can be set to true if cache[flag'] = false;
        //
        // you have to set cache[flag] = false if there is no path to go to a state where the other will lose
        // or in other word, cache[flag'] == true in all cases;
        //
		return helper(maxChoosableInteger, desiredTotal, flag, cache);
	}
private:
	bool helper(int maxRange, int target, int flag, unordered_map<int, bool>& cache) {
		if (cache.count(flag)) {
			return cache[flag];
		}
        // determine the value of cache[flag]
		for (int i = 0; i < maxRange; ++i) {
			int probe = 1 << i;
            if ((flag & probe) == 0) { // int (i + 1) has not been picked
                int value = i + 1;     // going to pick value
                // case 1
                // base case
                if (target <= value) {
                    cache[flag] = true;
                    return true;
                }
                // case 2
                if (!(helper(maxRange, target - value, flag | probe, cache))) {
                    // cache[flag | probe] has been marked as false;
                    return cache[flag] = true;
                }
            }
        }

        // have tried all possible
        // all cache[flag | probe] has been marked as true;
        // then cache[flag] = false; // lose state
        return cache[flag] = false;
	}
};

int main() {

	Solution s;

	return 0;
}
