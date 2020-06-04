#include "common.h"
class Solution {
	//https://www.cnblogs.com/grandyang/p/11300071.html
public:
	// method 1), priority_queue
	int shortestSubarray_pq(vector<int>& A, int K) {
		// pair<int, in> first is the sum of A[0..i], second is the end index
		int n = A.size();
		int result = INT_MAX;
		int sum = 0;
		priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min heap
		for (int i = 0; i < n; ++i) {
			sum += A[i];
			if (sum >= K) {
				result = min(result, i + 1); // A[0...i]
			}
			while (!pq.empty() && sum - pq.top().first >= K) {
                // only for index ending at i
				result = min(result, i + 1 - pq.top().second);
				pq.pop();
			}
			pq.push({ sum, i });
		}
		return result == INT_MAX ? -1 : result;
	}
	// method 2: deque
	// https://buptwc.com/2018/07/02/Leetcode-862-Shortest-Subarray-with-Sum-at-Least-K/
	// A = [4, -1, 2, 3], K = 5, then prefixSum = [0 , 4, 3, 5, 8]
	// 4 < K, is better than 0, keep it
	// 3 < K&& 3 < 4,  4 should be dropped, why?
	// we need to get a larger prefixSum so that the difference can be >= K while keep the length of subarray as short as possible
	// 3 can make the difference larger and the length shorter
	int shortestSubarray(vector<int>& A, int K) {
		int result = INT_MAX;
		int n = A.size();
		vector<int> prefixSum(n + 1, 0);
		deque<int> dq;
		for (int i = 1; i <= n; ++i) {
			prefixSum[i] = A[i - 1] + prefixSum[i - 1];
		}
		for (int i = 0; i <= n; ++i) {
			while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= K) {
				result = min(result, i - dq.front());
				dq.pop_front();
			}
			// note: at this moment  prefixSum[i] - prefixSum[dq.front()]  < K
			// we may be able to drop some candidates from deque
			while (!dq.empty() && prefixSum[i] <= prefixSum[dq.back()]) { // !!!!
				dq.pop_back();
			}
			dq.push_back(i);
		}
		return result == INT_MAX ? -1 : result;
	}

};

int main() {

	Solution s;

	return 0;
}
