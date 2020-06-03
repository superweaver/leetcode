#include "common.h"
class Solution {
public:
	bool splitArraySameAverage(vector<int>& A) {
		// assume A can be split into left and right
		// and average(left) == average(right),
		// then average(A) == average(left) == average(right)
		// sum(A) * left.size() / A.size() must be integer
		if (A.empty()) return false;
		int n = A.size();
		int sum = 0;
		for (auto i : A) {
			sum += i;
		}
		vector<int> candidate;
		for (int i = 1; i <= n - i; ++i) {
			if ((sum * i) % n == 0) {
				candidate.push_back(i);
			}
		}
		if (candidate.empty()) {
			return false;
		}
		sort(A.begin(), A.end());
		for (auto i : candidate) {
			int target = i * sum / n;
			if (dfs(A, target, i, 0, 0, 0)) {
				return true;
			}
		}
		return false;
	}
private:
	bool dfs(const vector<int>&A, int target, int targetsize, int start, int currentsize, int currentsum) {
		// check if you can find a subsequence of A, whose size = size and sum = target
		if (start >= int(A.size())) {
			return currentsize == targetsize && (currentsum == target);
		}
		if (currentsize > targetsize) return false;
		if (currentsize == targetsize) {
			return currentsum == target;
		}
		// use it
		int count = 0;
		for (size_t i = start; i < A.size(); ++i) {
			if (A[i] == A[start]) {
				count++;
			} else{
                break;
            }
		}
		for (int i = 1; i <= count; ++i) { // key :)
			if (dfs(A, target, targetsize, start + count, currentsize + i, i*A[start] + currentsum)) {
				return true;
			}
		}
		if ((int)A.size() - (start + 1) >= targetsize - currentsize)
			return dfs(A, target, targetsize, start + 1, currentsize, currentsum);
		else
			return false;
	}
};

class Solution_my {
public:
	bool splitArraySameAverage(vector<int>& A) {
		// assume A can be split into left and right
		// and average(left) == average(right),
		// then average(A) == average(left) == average(right)
		// sum(A) * left.size() / A.size() must be integer
		if (A.empty()) return false;
		int n = A.size();
		int sum = 0;
		for (auto i : A) {
			sum += i;
		}
		vector<int> candidate;
		for (int i = 1; i <= n - i; ++i) {
			if ((sum * i) % n == 0) {
                // (i * sum / n) is interger
				candidate.push_back(i);
			}
		}
		if (candidate.empty()) {
			return false;
		}
		sort(A.begin(), A.end());
		for (auto i : candidate) {
			int target = i * sum / n; // this is partial sum, size is i
			if (dfs(A, target, i, 0, 0, 0)) {
				return true;
			}
		}
		return false;
	}
private:
	bool dfs(const vector<int>&A, int target, int targetsize, int start, int currentsize, int currentsum) {
		// check if you can find a subsequence of A, whose size = size and sum = target
		if (start >= int(A.size())) {
			return currentsize == targetsize && (currentsum == target);
		}
		if (currentsize > targetsize) return false;
		if (currentsize == targetsize) {
			return currentsum == target;
		}
		// use it
		int count = 0;
		for (size_t i = start; i < A.size(); ++i) {
			if (A[i] == A[start]) {
				count++;
			}
		}
		for (int i = 1; i <= count; ++i) { // key :)
			if (dfs(A, target, targetsize, start + count, currentsize + i, i*A[start] + currentsum)) {
				return true;
			}
		}
		if ((int)A.size() - (start + 1) >= targetsize - currentsize) 
			return dfs(A, target, targetsize, start + 1, currentsize, currentsum);
		else
            // trim
            // impossible to get  targetsize
            return false;
	}
};

int main() {

	Solution s;

	return 0;
}
