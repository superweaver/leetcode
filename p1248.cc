#include "common.h"
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k)
    {
        int n = nums.size();
        queue<int> q;
        int result = 0;
		int next = 0;
		int last = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] & 1) {
                q.push(i);
                if (q.size() == (size_t)k) {
					last = i;
					next = i + 1;
					break;
                }
            }
        }
        if (q.size() < size_t(k)) {
			return result;
		}
		// trick
		nums.push_back(1);
		n++;
		int pre = -1; // !!!
		for (; next < n; ++next) {
            if (nums[next] & 1) {
                //result += (q.front() - pre) * (next - q.back());
				result += (q.front() - pre) * (next - last);
				pre = q.front();
				q.pop();
				last = next;
				q.push(next);
            }
        }
		nums.pop_back();
		return result;
    }
};

int main()
{
	vector<int> nums = {1,1,2,1,1};
	int k = 3; // 2
	nums = {2,4,6}, k = 1; // 0
	nums = {2,2,2,1,2,2,1,2,2,2}, k = 2;
    Solution s;
	cout << s.numberOfSubarrays(nums, k) << endl;

    return 0;
}
