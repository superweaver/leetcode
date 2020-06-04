#include "common.h"
class Solution {
    // https://www.cnblogs.com/grandyang/p/11329482.html
  public:
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int K) {
        // paid in proportional to quality
        // so the payment = ratio * sum(quality of K workers)
        // and ratio >= ratio of any worker in the workers
        vector<pair<double, int>> cache;
        int n = quality.size();
        for (int i = 0; i < n; ++i) {
            cache.push_back({double(wage[i]) / quality[i], quality[i]});
        }
        sort(cache.begin(), cache.end());
        double result = numeric_limits<double>::max();
        priority_queue<int> pq; // max heap
        int quality_sum = 0;
        for (auto &w : cache) {
            quality_sum += w.second;
            pq.push(w.second);
            if ((int)pq.size() > K) {
                quality_sum -= pq.top(); // remove the largest quality
                // why is this safe?
                // even the pq.top() == w.second, it is still safe
                // assume pq.top() == w.second, then quality_sum doesn't change comparing with
                // previous quality_sum when qp.size() == K however, previous ratio is <= w.first
                // since cache is sorted then  quality_sum * w.first >= previous result if pq.top()
                // != w.second, then quality_sum decreases while the ratio increases to w.first need
                // to check
                pq.pop();
            }
            if (pq.size() == K) {
                result = min(result, quality_sum * w.first);
            }
        }
        return result;
    }
};

class Solution2 {
    // https://www.cnblogs.com/grandyang/p/11329482.html
  public:
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int K) {
        // paid in proportional to quality
        // so the payment = ratio * sum(quality of K workers)
        // and ratio >= ratio of any worker in the workers
        vector<pair<double, int>> cache;
        int n = quality.size();
        for (int i = 0; i < n; ++i) {
            cache.push_back({double(wage[i]) / quality[i], quality[i]});
        }
        sort(cache.begin(), cache.end());
        double result = numeric_limits<double>::max();
        priority_queue<int> pq; // max heap
        int quality_sum = 0;
        for (auto &w : cache) {
            quality_sum += w.second;
            pq.push(w.second);
            if ((int)pq.size() > K) {
                quality_sum -= pq.top(); // remove the largest quality
                pq.pop();
            }
            if (pq.size() == K) {
                result = min(result, quality_sum * w.first);
            }
        }
        return result;
    }
};

int main() {

	Solution s;

	return 0;
}
