#include "common.h"
// https://leetcode.com/problems/most-profit-assigning-work/discuss/127031/C%2B%2BJavaPython-Sort-and-Two-pointer
// 
class Solution {
public:
  int maxProfitAssignment_ref(vector<int> &difficulty, vector<int> &profit, vector<int> &worker) {
      // solution 1
      // zip difficulty and profit as jobs.
      // sort jobs and sort 'worker'.
      // Use 2 pointers. For each worker, find his maximum profit best he can make under his
      // ability.

      vector<pair<int, int>> jobs;
      int N = profit.size(), res = 0, i = 0, best = 0;
      for (int j = 0; j < N; ++j) {
          jobs.push_back(make_pair(difficulty[j], profit[j]));
      }
      sort(jobs.begin(), jobs.end());
      sort(worker.begin(), worker.end());
      for (int &ability : worker) {
          while (i < N && ability >= jobs[i].first) {
              best = max(jobs[i++].second, best);
          }
          res += best;
      }
      return res;
  }

  int maxProfitAssignment_ref2(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
      // Use a treemap<difficulty, profit>
      // Go through the treemap once, find the max profit best for each difficulty.
      //
      int N = profit.size(), res = 0, i = 0, best = 0;
      map<int, int> jobs;
      jobs[0] = 0; // nice
      for (int j = 0; j < N; ++j) {
          jobs[difficulty[j]] = max(jobs[difficulty[j]], profit[j]);
      }

      for (auto &it : jobs) {
          // update the max profit for such difficulty
          it.second = best = max(best, it.second);
      }
      for (int &ability : worker) {
          res += (--jobs.upper_bound(ability))->second;
      }
      return res;
    }

    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
		// sort according to profit instead of difficulty
        // difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job.
		int n = difficulty.size();
		vector<pair<int, int>> D; // difficulity of ith job -> index = i
        for (int i = 0; i < n; ++i) {
            D.push_back({difficulty[i], i});
        }
        sort(D.begin(), D.end());

		vector<int> d;
		vector<int> p;
		d.push_back(D[0].first);
		p.push_back(profit[D[0].second]);

		for (int i = 1; i < n;) {
            // for the same difficulity, we don't do the one with largest profit
			while (i < n && D[i].first == d.back()) {
				p.back() = max(p.back(), profit[D[i].second]);
				i++;
			}

			if (i < n && D[i].first > d.back()) {
                
				if (profit[D[i].second] > p.back()) {
					d.push_back(D[i].first);
					p.push_back(profit[D[i].second]);
				}
                // else {// harder job with less profit, we just ignore it }
            }
			++i;
		}

		int result = 0;
		sort(worker.begin(), worker.end());
		size_t i = 0;
		while (i < worker.size() && worker[i] < d[0]) {
			i++;
		}

		for (size_t j = 0; j < d.size(); ++j) {
			int next = (j + 1) < d.size() ? d[j + 1] : INT_MAX;
			int count = 0;
			while (i < worker.size() && worker[i] < next) {
				i++;
				count++;
			}
			result += count * p[j];
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
