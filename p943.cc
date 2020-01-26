#include "common.h"
class Solution {
    public:
        // https://zxi.mytechroad.com/blog/searching/leetcode-943-find-the-shortest-superstring/
        //  1) dfs
        //  2) dp
        string shortestSuperstring_dfs(vector<string>& A) {
            int n = A.size();  
            costs = vector<vector<int>>(n, vector<int>(n, 0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j) continue;
                    costs[i][j] = calculateCost(A[i], A[j]);
                }
            }
            int shortestLen = INT_MAX;
            vector<int> shortestPath;
            vector<int> path(n, 0);
            dfs(A, 0, 0, 0, path, shortestLen, shortestPath);
            string result = A[shortestPath[0]];
            for (size_t i = 1; i < shortestPath.size(); ++i) {
                int pre = shortestPath[i-1];
                int current = shortestPath[i];
                result += A[current].substr(A[current].size() - costs[pre][current]);
            }
            return result; 
        }

        string shortestSuperstring(vector<string>& A) {
            int n = A.size();  
            costs = vector<vector<int>>(n, vector<int>(n, 0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j) continue;
                    costs[i][j] = calculateCost(A[i], A[j]);
                }
            }
            // dp[s][i] is the min cost to achieve state s and the sequence ends at A[
            // base case: dp[1 << i][i] = A[i].size();
            // transition:
            // dp[s][i] = min{dp[s-(1<<i)][j] + costs[j][i]}
            // return min(dp[2^n-1][*])
            int totalStates = 1 << n;
            vector<vector<int>> dp (totalStates, vector<int>(n, INT_MAX / 2));
            vector<vector<int>> preStr(totalStates, vector<int>(n, -1)); // store the index of previous string
            for (int i = 0; i < n; ++i) {
                dp[1 << i][i] = A[i].size();
            }
            // order is importanct
            for (int s = 1; s < totalStates; ++s) {
                for (int i = 0; i < n; ++i) {
                    // check if state s include node i
                    if (!(s & (1 << i))) {
                        continue;
                    }
                    int ps = s & ~(1 << i);  // previous state
                    // we can also try all ones in ps
                    for (int j = 0; j < n; ++j) {
                        if (dp[ps][j] + costs[j][i]  < dp[s][i]) {
                            dp[s][i] = dp[ps][j] + costs[j][i];
                            preStr[s][i] = j;
                        }
                    }
                }
            }
            auto& v = dp.back(); // dp[totalStates-1];
            int index  = 0;
            for (int i = 0; i < n; ++i) {
                if (v[i]  < v[index]) {
                    index = i;
                }
            }
            string result;
            int state = totalStates - 1;
            while(state) {
                int preIndex = preStr[state][index];
                if (preIndex < 0) {
                    result = A[index] + result;
                } else {
                    result = A[index].substr(A[index].size() - costs[preIndex][index]) + result;
                }
                //state -= (1 << index); // set bit for index to 0;
                state &= ~(1 << index); // set bit for index to 0;
                index = preIndex;
            }
            return result;
        }
    private:
        vector<vector<int>> costs;
        int calculateCost(const string& a, const string& b) {
            // put a before b, and try to get min length of concatination of a + b
            // return the leftover length of b
            if (a == b) {
                return 0;
            }
            int cost = b.size();
            int len = min(a.size(), b.size());
            for (int l = 1; l <= len; ++l) {
                if (a.substr(a.size() - l) == b.substr(0, l)) {
                    cost = b.size() - l;
                }
            }
            return cost;
        }
        void dfs(const vector<string>& A, size_t searchdepth, int usedstr, int currentLen, vector<int>&path, int& shortestLen, vector<int>& shortestPath) {
            if (currentLen >= shortestLen) {
                // no need to continue
                return;
            }

            if (searchdepth == A.size()) {
                // update 
                shortestLen = currentLen; 
                shortestPath = path;
                return ;
            }
            for (size_t i = 0; i < A.size(); ++i) {
                // check if this strign has been used
                if (usedstr & (1 << i)) {
                    // used
                    continue;
                }
                path[searchdepth] = i;
                // pay attention to get previous string
                // the index is path[searchdepth-1]
                dfs(A, searchdepth + 1, usedstr | (1 << i), (searchdepth == 0) ? A[i].size() : (currentLen + costs[path[searchdepth - 1]][i]), 
                        path, shortestLen, shortestPath);
            }

        }
};

int main() {
    vector<string> A = {"catg","ctaagt","gcta","ttca","atgcatc"};
    Solution s;
    auto r = s.shortestSuperstring(A);
    cout << r.size() << ":" << r << endl;

    //r = "gctaagttcatgcatc"; // 16
    //cout << r.size() << ":" << r << endl;
    return 0;
}
