#include "common.h"
class Solution {
public:
    int minFlips(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int N = m * n; //
		vector<int> visited(1 << N, 0); 
        int target = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                target += (mat[i][j] << (i*n+j));
            }
        }

        //cout << "target:" << target << endl;
        queue<int> q;
        q.push(0);
        int step = 0;
        visited[0] = 1;
		while(!q.empty()) {
            int size = q.size();
            //cout << size << endl;
            while(size--) {
				auto current = q.front();
                //cout << current << endl;
				q.pop();
				if(current == target)
				{
					return step;
				}
				for(int i = 0; i < N; ++i)
				{
					int next = current;
					int r = i / n;
					int c = i % n;
					// flip [r, c]
					next ^= (1 << i);
					for(int k = 0; k < 4; ++k)
					{
						int nr = r + dirs[k];
						int nc = c + dirs[k + 1];
						if(nr < 0 || nr >= m || nc < 0 || nc >= n)
						{
							continue;
						}
						int index = nr * n + nc;
						next ^= (1 << index);
					}
					if(!visited[next])
					{
						visited[next] = 1;
						q.push(next);
					}
				}
			}
			step++;
		}
		return -1;
	}
private:
    const vector<int> dirs = {0, 1, 0, -1, 0};
};

int main() {
	vector<vector<int>> mat = {{0, 0}, {0, 1}}; // 3
//	mat = {{1, 1, 1}, {1, 0, 1}, {0, 0, 0}}; // 6
//    mat = {{1,0,0},{1,0,0}}; // -1

	Solution s;
    cout << s.minFlips(mat) << endl;

	return 0;
}
