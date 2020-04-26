#include "common.h"
class SegmentTree
{
public:
	SegmentTree(const vector<int>& arr)
	{
		assert(arr.size());
		this->arr.assign(arr.begin(), arr.end());
		size_t n = 1;
		while(n < arr.size())
		{
			n <<= 1;
		}
		tree.assign(n << 1, 0);
		build_tree(0, 0, (int)arr.size() - 1);
	}
	// set arr[i] = val;
	void update(int index, int val)
	{
		if(arr[index] == val)
		{
			return;
		}
		update_implement(0, 0, (int)arr.size() - 1, index, val);
	}
	// return the summation of arr[left...right]
	// return the max of arr[left...right]
	int query(int left, int right)
	{
		assert(left >= 0);
		assert(right < arr.size());
		return query_implement(0, 0, (int)arr.size() - 1, left, right);
	}

private:
	// no need to keep original array;
	vector<int> arr;
	vector<int> tree;
	void build_tree(int node, int start, int end)
	{
		if(start == end)
		{
			tree[node] = arr[start];
			//cout << node << ":" << tree[node] << endl;
			return;
		}
		// start < end
		int mid = start + ((end - start) >> 1);
		int left_node = (node << 1) + 1;
		int right_node = (node << 1) + 2;
		build_tree(left_node, start, mid);
		build_tree(right_node, mid + 1, end);
		tree[node] = max(tree[left_node], tree[right_node]);
		//tree[node] = tree[left_node] + tree[right_node];
	}
	void update_implement(int node, int start, int end, int index, int val)
	{
		if(start == end)
		{
			tree[node] = arr[index] = val;
			return;
		}
		// start < end
		int mid = start + ((end - start) >> 1);
		int left_node = (node << 1) + 1;
		int right_node = (node << 1) + 2;
		if(index <= mid)
		{
			update_implement(left_node, start, mid, index, val);
		}
		else
		{
			update_implement(right_node, mid + 1, end, index, val);
		}
		// update tree[node]
		//tree[node] = tree[left_node] + tree[right_node];
		tree[node] = max(tree[left_node], tree[right_node]);
	}

	int query_implement(int node, int start, int end, int left, int right)
	{
		if(end < left || start > right)
		{
			// no overlap between the range covered by node
			return 0;
		}
		else if(left <= start && end <= right)
		{
			// [left, right] fully cover node range [start, end]
			return tree[node];
		}
		else
		{
			// need both part of left subtree and right subtree
			int mid = start + ((end - start) >> 1);
			int left_node = (node << 1) + 1;
			int right_node = (node << 1) + 2;
			//return query_implement(left_node, start, mid, left, right) + query_implement(right_node, mid + 1, end, left, right);
			return max(query_implement(left_node, start, mid, left, right),
					   query_implement(right_node, mid + 1, end, left, right));
		}
	}
};

class Solution
{
public:
	int constrainedSubsetSum(vector<int>& nums, int k) {
        deque<pair<int, int>> q; // dp[i], i
        // q is monotonic decreasing
        int n = nums.size();
        int result = nums[0];
		q.push_back({nums[0], 0});
		for(int i = 1; i < n; ++i)
		{
			// dp[i] = nums[i] + max(0, q.front().first);
			int dp = nums[i] + max(0, q.front().first);
			result = max(dp, result);

			// update q with (dp, i)
			while(!q.empty() && q.back().first <= dp)
			{
				q.pop_back();
			}

            // this is nice
			while(!q.empty() && q.front().second <= i - k)
			{
				q.pop_front();
			}

			q.push_back({dp, i});
		}

		return result;
    }

	int constrainedSubsetSum_segmenttree(vector<int>& nums, int k)
	{
		int result = nums[0];
        vector<int> pre;
        pre.push_back(nums[0]);
        int max_pre = nums[0];

		for(int i = 1; i < k; ++i)
		{
			int temp = max(nums[i], nums[i] + max_pre);
            pre.push_back(temp);
            max_pre = max(max_pre, temp);
			result = max(result, temp);
		}
        SegmentTree st(pre);
		int n = nums.size();
		for(int i = k; i < n; ++i)
		{
			int temp = max(nums[i], nums[i] + st.query(0, k - 1));
            st.update(i % k, temp);
			result = max(result, temp);
		}
		return result;
	}
};

int main()
{
	vector<int> nums = {10, 2, -10, 5, 20};
	int k = 2; // 37

	nums = {-1, -2, -3}, k = 1; // -1
	nums = {10, -2, -10, -5, 20}, k = 2; // 23

	Solution s;
	cout << s.constrainedSubsetSum(nums, k) << endl;

	return 0;
}
