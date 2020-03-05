#include "common.h"
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
		int n = arr.size();
		queue<int> q;	
		q.push(start);
        arr[start] = -arr[start] - 1;
        while (!q.empty()) {
			auto c = q.front();
			q.pop();
			int oldvalue = - (arr[c] + 1);
            if (!oldvalue) {
				return true;
            }
			int next = c + oldvalue;
			if (next >= 0 && next < n && arr[next] >= 0) {
				q.push(next);
				arr[next] = -arr[next] - 1;
			}
            next = c - oldvalue;
            if (next >= 0 && next < n && arr[next] >= 0) {
				q.push(next);
				arr[next] = -arr[next] - 1;
			}
        }
		return false;
    }
};

int main() {

	vector<int> arr = {4,2,3,0,3,1,2};
	int start = 5; // true
	arr = {4,2,3,0,3,1,2}, start = 0; // true
	arr = {3,0,2,1,2}, start = 2; // false;
	Solution s;
	cout << s.canReach(arr, start) << endl;


	return 0;
}
