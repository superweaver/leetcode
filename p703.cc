#include "common.h"
class KthLargest {
    // Design a class to find the kth largest element in a stream
    // stupid description, largest!!!
    //
    // kth largest-> need to keep a k size priority_queue to keep k largest value
    // and return its top
  public:
	KthLargest(int k, vector<int>& nums) {
		// n >= k - 1
		int n = nums.size();
		this->k = k;
		if (n > k) {
			for (int i = 0; i < k; i++) {
				q.push(nums[i]);
			}
			for (int i = k; i < n; ++i) {
				if (nums[i] > q.top()) {
					q.push(nums[i]);
					q.pop();
				}
			}
		}
		else {
			for (auto i : nums) {
				q.push(i);
			}
		}

	}

	int add(int val) {
		if (q.size() < k) {
			q.push(val);
		}
		else {
			if (val > q.top()) {
				q.push(val);
				q.pop();
			}
		}
		return q.top();
	}
private:
	priority_queue<int, vector<int>, greater<int>> q;
	int k;
};

int main() {

	Solution s;

	return 0;
}
