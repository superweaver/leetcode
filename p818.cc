#include "common.h"
class Solution {
public:
	//https://www.cnblogs.com/grandyang/p/10360655.html
	int racecar(int target) {
		// dp
		// dp[i] is the min step to get position i
        //
		// dp[i] is the min of following
		// 1) let j to be any position before i by continuing going right,
		// then turn left and go some distances k, (j - k) > 0, then turn right again
		// note k can be 0!!!!!!!!!
		// step = dp(j-k) + 2 + count1 + count2, where j = 2^count1-1, k = 2^count2 -1;, k < j
		// 2) 2^count1 -1 == target, return count1
		// 3) go beyond target to j = 2^(count1+1) -1 and turn left, step = 2 + dp[j-i]
		int upper = target + 1;
		vector<int> dp(upper, 0);
		for (int i = 1; i < upper; ++i) {
			dp[i] = INT_MAX;
			// 1)
			int count1 = 1;
			int j = (1 << count1) - 1;
			for (; j < i; j = (1 << (++count1)) - 1) {
				// k can be zero
				for (int count2 = 0, k = 0; k < j; k = (1 << (++count2)) - 1) {
					dp[i] = min(dp[i], 2 + count1 + count2 + dp[i - j + k]);
				}
			}
			//  j >= i
			if (j == i) {
				// case 2
				dp[i] = count1;
			}
			else {
				// reverse once
				// case 3
				dp[i] = min(dp[i], count1 + 1 + dp[j - i]);
			}
		}
		return dp[target];
	}
};


class Solution_bfs {
public:
	//https://www.cnblogs.com/grandyang/p/10360655.html
	int racecar(int target) {
		// BFS
		// car's state can be expressed as (position, speed)
		// at any state, there aret two options
		// 1) continue -> (position + speed, 2*speed)
		// 2) reverse, -> (position, speed > 0 ? -1 : 1)
		int step = 0;
		int upper = 2 * target;
		queue<pair<int, int> > q;
		unordered_set<int> visited;
		//  key = ((2*target+speed) << 15) + pos
		q.push({ 0, 1 });
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				auto p = q.front();
				q.pop();
				int currentpos = p.first;
				int currentspeed = p.second;
				if (currentpos == target) {
					return step;
				}
				// case 1 : continue
				int newpos = currentpos + currentspeed;
				int newspeed = currentspeed * 2;
				if (newpos > 0 && newpos < upper) {
					int key = ((upper + newspeed) << 15) + newpos;
					if (!visited.count(key)) {
						visited.insert(key);
						q.push({ newpos, newspeed });

					}
				}
				// case 2: reverse
				newpos = currentpos;
				newspeed = currentspeed > 0 ? -1 : 1;
				if (newpos > 0 && newpos < upper) {
					int key = ((upper + newspeed) << 15) + newpos;
					if (!visited.count(key)) {
						visited.insert(key);
						q.push({ newpos, newspeed });

					}
				}
			}
			step++;
		}
		return -1;
	}
};

int main() {

	Solution s;

	return 0;
}
