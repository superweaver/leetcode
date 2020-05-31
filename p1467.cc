#include "common.h"
class Solution {
public:
    double getProbability(vector<int>& balls) {
        int k = balls.size();
        int n = accumulate(balls.begin(), balls.end(), 0) / 2;
        vector<int> suffix_sum(k + 1, 0);
        for (int i = k - 1; i >= 0; --i) {
            suffix_sum[i] = balls[i] + suffix_sum[i + 1];
        }
        //  get c(n, k)
        //  c(n, k) = c(n-1, k) + c(n-1, k-1)
        vector<vector<long long>> comb(7);
        comb[0].push_back(1);
        for (int i = 1; i <= 6; ++i) {
            comb[i].push_back(1);
            for (int j = 1; j <= i; j++) {
                if (j > i - j) {
                    comb[i].push_back(comb[i][i-j]);
                } else {
                    comb[i].push_back(comb[i - 1][j] + comb[i - 1][j - 1]);
                }
            }
        }
        long long result = 0;
        vector<int> path;
        vector<long long> combinations;
        int leftcolor = 0;
        int rightcolor = k;
        dfs(balls, 0, 0, path, combinations, result, suffix_sum, n, comb, leftcolor, rightcolor);
        double r =  result;
        // r / C(2n, n)
        for (int i = 0; i < n; ++i) {
            r *= (n-i);
            r /= (2*n-i);
        }
        return r;
    }

  private:
    void dfs(vector<int> &balls, int start, int picks, vector<int> &path,
             vector<long long> &combinations, long long &result, vector<int> &suffix_sum, int n,
             vector<vector<long long>> &comb, int leftcolor, int rightcolor) {
        if (picks == n) {
            if (leftcolor == rightcolor) {
                // and leftcolor == rightcolor
                // cout << "leftcolor = " << leftcolor << ", rightcolor = " << rightcolor << endl;
                long long count = 1;
                for (auto c : combinations) {
                    count *= c;
                }
                result += count;
            }
            return;
        }
        if (start >= suffix_sum.size()) {
            return;
        }
        if (picks + suffix_sum[start] < n) {
            return;
        }
        if (leftcolor > rightcolor) {
            return;
        }
        if (start >= balls.size()) {
            return;
        }
        for (int i = 0; i <= balls[start]; ++i) {
            int nextleftcolor = leftcolor + (i > 0);
            int nextrightcolor = rightcolor - (i == balls[start]);
            if (nextleftcolor <= nextrightcolor) {
                if (picks +i > n) {
                    break;
                }
                picks += i;
                path.push_back(i);
                combinations.push_back(comb[balls[start]][i]);
                dfs(balls, start + 1, picks, path, combinations, result, suffix_sum, n, comb,
                    nextleftcolor, nextrightcolor);
                combinations.pop_back();
                path.pop_back();
                picks -= i;
            }
        }
    }
    //long long combination(int n, int k) { return 0; }
};

int main() {
    vector<int> balls = {1, 1}; // 1
    balls = {2,1,1}; // 2/3
    balls = {1,2,1,2}; // 0.6
    balls = {3,2,1}; // 0.3
    balls = {6, 6, 6, 6, 6, 6}; 
    balls = {6, 6, 6, 6, 6, 6, 6, 6}; 

    Solution s;
    cout << s.getProbability(balls) << endl;
	return 0;
}
