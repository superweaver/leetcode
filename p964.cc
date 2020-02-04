#include "common.h"
//https://blog.csdn.net/lemonmillie/article/details/86628980
//https://zhanghuimeng.github.io/post/leetcode-964-least-operators-to-express-number/
//https://zxi.mytechroad.com/blog/uncategorized/leetcode-964-least-operators-to-express-number/
class Solution {
public:
	// analysis
	// 2 <= x <= 100
    // 1 <= target <= 2 * 10^8
	// target can be expressed in following form
	//
	// ----------------------target = sum(ai * x^i)          -------------------     formula 
	//
	// to get x^i, you need m operators m = (i == 0) ? 2 : (i); // +- is also included
	// the total operators will be sum(ai * (mi)) - 1
	// how to get ai
	// 1) directly use x^i with number of ai , total operators = ai * (mi + 1)
	// 2) write ai as (x-bi) * x^i, borrow a x^(i+1) from higher weight one, and use a negative bi = x-ai
	// note if we use method 2), the bollowed one will be rearranged into upper weight x^(i+1) until the max one i^n, where a -i^(n+1) must applied
	// so there may be two forms to get minimal operators for target
	
	// form 0: target = sum(ai * x^i), i = 0, 1, ..., n
	// form 1: target = a0 + a1*x + ... + an*x^n - x^(n+1)
	// dp[i][0] is the minimal operators to construct first (i+1) terms of formula using form0
	// dp[i][1] is the minimal operators to construct first (i+1) terms of formula using form1
	// 
	// dp[i+1][0] = min (a, b)
	//  a = dp[i][0] + a_i+1 * m_i+1
	//  b = dp[i][1] + (a_i+1 + 1) * m_i+1
	//
	//  dp[i+1][1] = min(c, d)
	//  c = dp[i][0] + abs(x-a_i+1)* m_i+1
	//  c = dp[i][1] + abs(x - (a_i+1 + 1)) * m_i+1
	//  refer to https://zhanghuimeng.github.io/post/leetcode-964-least-operators-to-express-number/
	//  at last return dp[n][0] - 1; (first operator + or - is not needed)
    int leastOpsExpressTarget(int x, int target) {
		// convert target to base x
		vector<int> coef;
		while (target) {
			coef.push_back(target % x);
			target /= x;
		}
		int n = coef.size();
		coef.push_back(0); // tricky
		vector<vector<int>> dp(n+1, vector<int>(2, 0)); 
		// base case 
		dp[0][0] = 2 * coef[0];
		dp[0][1] = 2 * abs(x - coef[0]);
		for (int i = 1; i <= n; ++i) {
			dp[i][0] = min(dp[i-1][0] + coef[i] * i, dp[i-1][1] +( coef[i] + 1) * i);
			dp[i][1] = min(dp[i-1][0] + abs(x - coef[i]) * i, dp[i-1][1] + abs(x - (1 + coef[i])) * i);
		}
		return dp[n][0] - 1; // tricky
	}
	// convert it to a graph problem
	int leastOpsExpressTarget_pq(int x, int target) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
		unordered_set<int> s;
		q.emplace(0, target); // 0 is steps, target is current node
							  // find the shortest path to node 0
		while (!q.empty()) {
			const int c = q.top().first; // current steps
			const int t = q.top().second;
			q.pop();
			if (t == 0) return c - 1;
			if (s.count(t)) continue; //have visited previously by another path
			s.insert(t); // not visited ? now visit it
			int n = log(t) / log(x);
			int l = t - pow(x, n);        // l <= t
			q.emplace(c + (n == 0 ? 2 : n), l);
			// try anoterh way: get a bigger number and x^(n+1) and then get back
			int r = pow(x, n + 1) - t;        
			q.emplace(c + n + 1, r);
		}
		return -1;
	}
public:
  int leastOpsExpressTarget_dp(int x, int target) {
    return dp(x, target);
  }
private:
  unordered_map<int, int> m_;
  int dp(int x, int t) {
	  if (t == 0) return 0;
	  if (t < x) return min(2 * t - 1, 2 * (x - t));
	  if (m_.count(t)) return m_.at(t);
	  int k = log(t) / log(x);
	  long p = pow(x, k);
	  if (t == p) return m_[t] = k - 1;
	  int ans = dp(x, t - p) + k; // t - p < t
	  long left = p * x - t;
	  if (0 <= left < t) // only rely on smaller sub-problems
		  ans = min(ans, dp(x, left) + k + 1);
	  return m_[t] = ans;
  }

};
int main() {
	int x = 5;
	int target = 501; // 8
	// x = 3, target = 19; // 5
	Solution s;
	cout << s.leastOpsExpressTarget(x, target) << endl;
	return 0;
}
