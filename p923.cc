#include "common.h"
class Solution {
  public:
    int threeSumMulti(vector<int> &A, int target) {
        const int Mod = (int)1e9 + 7;
        sort(A.begin(), A.end());
        unordered_map<int, int> count;
        for (auto i : A) {
            count[i]++;
        }
        vector<pair<int, int>> Ap;
        for (auto &p : count) {
            Ap.push_back({p.first, p.second});
        }
        sort(Ap.begin(), Ap.end());
        // no duplicate
        long long r = 0;
        int n = Ap.size();
        for (int a = 0; a < n; ++a) {
            if (3 * Ap[a].first > target) {
                break;
            }
            for (int b = a + 1, c = n - 1; b < c;) {
                if (Ap[a].first + Ap[b].first + Ap[c].first < target) {
                    b++;
                } else if (Ap[a].first + Ap[b].first + Ap[c].first > target) {
                    c--;
                } else {
                    r += (Ap[a].second * Ap[b].second * Ap[c].second);
                    r %= Mod;
                    b++;
                    c--;
                }
            }
        }
        // there is duplicate;
        for (int a = 0; a < n; ++a) {
            int ab = 2 * Ap[a].first;
            if (ab > target) {
                break;
            }
            long long C = Ap[a].second;
            if (C >= 2) {
                if (ab <= target && count.count(target - ab)) {
                    if (target - ab == Ap[a].first) { // thre of them are same
                        if (C >= 3) {
                            // Cn_3
                            r += (C * (C - 1) * (C - 2)) / 6;
                            r %= Mod;
                        }
                    } else {
                        r += (count[target - ab]) * (C * (C - 1) / 2);
                        r %= Mod;
                    }
                }
            }
        }
        return (int)r;
    }
};

int main() {

	Solution s;

	return 0;
}
