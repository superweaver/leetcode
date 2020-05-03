#include "common.h"
class Solution
{
public:
	int longestSubarray(vector<int>& A, int limit)
	{
        //https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/discuss/609771/JavaC%2B%2BPython-Deques-O(N)
		deque<int> maxd, mind;
		int i = 0, j;
		for(j = 0; j < A.size(); ++j)
		{
			while(!maxd.empty() && A[j] > maxd.back())
				maxd.pop_back();
			while(!mind.empty() && A[j] < mind.back())
				mind.pop_back();
			maxd.push_back(A[j]);
			mind.push_back(A[j]);
			// trick here
			// if (maxd.front() - mind.front() <= limit) {
			//    there is only update for j, length increase
			// } else {
            //    there is both update for j and i, j - i is not changed
            // }
			if(maxd.front() - mind.front() > limit)
			{
				if(maxd.front() == A[i])
					maxd.pop_front();
				if(mind.front() == A[i])
					mind.pop_front();
				++i; // nice
			}
		}
		return j - i;
	}

	int longestSubarray_leetcode(vector<int>& nums, int limit)
	{
		int ans = 0, lo = 0, hi = 0;
        // lo is left index
        // hi is right index
		deque<int> minQ, maxQ;
		while(hi < nums.size())
		{
			while(!minQ.empty() && nums[minQ.back()] >= nums[hi])
			{
				minQ.pop_back();
			}
			minQ.push_back(hi);
			while(!maxQ.empty() && nums[maxQ.back()] <= nums[hi])
			{
				maxQ.pop_back();
			}
			maxQ.push_back(hi);
			int minVal = nums[minQ.front()], maxVal = nums[maxQ.front()];

			if(maxVal - minVal > limit)
			{
				// hi is not updated
				lo++;
				if(lo > minQ.front())
				{
					minQ.pop_front();
				}
				if(lo > maxQ.front())
				{
					maxQ.pop_front();
				}
			}
			else
			{
				ans = max(ans, hi - lo + 1);
				hi++;
			}
		}
		return ans;
	}
};

class Solution_my
{
public:
	int longestSubarray(vector<int>& nums, int limit)
	{
		int n = nums.size();
		deque<int> m;
		m.push_back(0);
		deque<int> M;
		M.push_back(0);
		vector<int> dp(n, 1);
		int r = 1;
		for(int i = 1; i < n; ++i)
		{
			int& v = nums[i];
			if(v <= nums[m.front()] + limit && v >= nums[M.front()] - limit)
			{
				dp[i] = dp[i - 1] + 1;
				r = max(dp[i], r);
				// update m and M
				while(!m.empty() && nums[m.back()] > v)
				{
					m.pop_back();
				}
				m.push_back(i);
				while(!M.empty() && nums[M.back()] < v)
				{
					M.pop_back();
				}
				M.push_back(i);
			}
			else
			{
				while(!m.empty() && v > nums[m.front()] + limit)
				{
					m.pop_front();
				}
				while(!m.empty() && nums[m.back()] > v)
				{
					m.pop_back();
				}
				m.push_back(i);

				while(!M.empty() && v < nums[M.front()] - limit)
				{
					M.pop_front();
				}
				while(!M.empty() && nums[M.back()] < v)
				{
					M.pop_back();
				}
				M.push_back(i);

				int index = min(m.front(), M.front());
				while(index >= 0 && v <= nums[index] + limit && v >= nums[index] - limit)
				{
					index--;
				}
				dp[i] = i - index;
				r = max(r, dp[i]);
			}
		}
		return r;
	}
};

int main()
{

	vector<int> nums = {10, 1, 2, 4, 7, 2, 9};
    int limit = 5;
/*
	nums.clear();
	for(int i = 0; i < 10000; ++i)
	{
		nums.push_back(i);
	}
    
*/
	//nums= {4,2,2,2,4,4,2,2};
	//limit = 0;
	Solution s;
	cout << s.longestSubarray(nums, limit) << endl;

	return 0;
}
