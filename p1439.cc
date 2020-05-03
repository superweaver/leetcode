#include "common.h"
class Solution
{
public:
	int kthSmallest_merge(vector<vector<int>>& mat, int k)
	{
		vector<int> row = mat[0]; // current cache with mat[0]
		for(int i = 1; i < mat.size(); ++i) // row index
		{
			vector<int> nr;       // next row
			const auto& v = mat[i];
			for(auto e : v) 
                // use element with next row to combine sub_sum for element from previous rows
			{
				for(auto cv : row)
				{
					nr.push_back(e + cv);
				}
			}
			sort(nr.begin(), nr.end());
			nr.resize(min(k, (int)nr.size()));
			row.swap(nr);
		}
		return row[k - 1];
	}

	int kthSmallest(vector<vector<int>>& mat, int k) // binary search and backtrack
	{
        // https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/discuss/610701
		int m = mat.size(), n = mat[0].size();
		int left = m, right = m * 5000, ans = -1;
		while(left <= right)
		{
			int mid = left + (right - left) / 2;
			int cnt = countArraysHaveSumLessOrEqual(mat, m, n, mid, 0, 0, k);
			if(cnt >= k)
			{
				ans = mid;
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		return ans;
	}
	int countArraysHaveSumLessOrEqual(
		vector<vector<int>>& mat, int m, int n, int targetSum, int r, int sum, int k)
	{
        // sum is the sum we have gotten with first r rows
		if(sum > targetSum) {
			return 0;
		}

		if(r == m) {
			return 1;
        }

		int ans = 0;
		for(int c = 0; c < n; ++c)
		{
            // pick mat[r][c]
			int cnt = countArraysHaveSumLessOrEqual(
				mat, m, n, targetSum, r + 1, sum + mat[r][c], k - ans);
			if(cnt == 0) {
                // no point to continue
				break;
            }
			ans += cnt;
			if(ans > k) {
				break; // prune when count > k
            }
		}
		return ans;
	}

	int kthSmallest_my(vector<vector<int>>& mat, int k)
	{
		int m = mat.size();
		int n = mat[0].size();
		// encode
		typedef pair<int, vector<int>> T;
		priority_queue<T, vector<T>, greater<T>> q;
		int sum = 0;
		for(int i = 0; i < m; ++i)
		{
			sum += mat[i][0];
		}
		q.push({sum, vector<int>(m, 0)});
		visited.insert(q.top().second);

		int index = 0;
		while(!q.empty())
		{
			auto c = q.top();
			q.pop();
			index++;
			sum = c.first;
			if(index == k)
			{
				return sum;
			}
			auto& v = c.second;
			for(int i = 0; i < m; ++i)
			{
				if(v[i] < n - 1)
				{
					auto column = v;
					column[i]++;
					if(!visited.count(column))
					{
						// has to ensure column has not been pushed in the past
						q.push({sum + mat[i][column[i]] - mat[i][column[i] - 1], column});
						visited.insert(column);
					}
				}
			}
		}
		return sum;
	}

private:
	set<vector<int>> visited;
};

int main()
{
	vector<vector<int>> mat = {{1, 1, 10}, {2, 2, 9}};
	int k = 7; // 12
	mat = {{1, 10, 10}, {1, 4, 5}, {2, 3, 6}}, k = 7; // 9
	mat = {{1, 3, 11}, {2, 4, 6}}, k = 9; // 17
//	mat = {{1, 3, 11}, {2, 4, 6}}, k = 5; //7

	Solution s;
	cout << s.kthSmallest(mat, k) << endl;
	cout << s.kthSmallest_merge(mat, k) << endl;

	return 0;
}
