#include "common.h"
// https://leetcode.com/problems/smallest-rotation-with-highest-score/discuss/118725/Easy-and-Concise-5-lines-Solution-C++JavaPython?page=2
class Solution {
  public:
    int bestRotation(vector<int> &A) {
        int n = A.size();
        vector<int> change(n, 0);
        for (int i = 0; i < n; ++i) {
            change[(i - A[i] + 1 + n) % n] -= 1;
        }
        for (int i = 1; i < n; ++i) {
            change[i] += change[i - 1] + 1;
        }
        return max_element(change.begin(), change.end()) - change.begin();
    }
};

class Solution_my {
  public:
    int bestRotation(vector<int> &A) {
        // use intervals
        int n = A.size();
        vector<pair<int, int>> intervals;
        for (int i = 0; i < n; ++i) {
            int ones = n - A[i];
            if (ones == n)
                continue; // no need to consider it
            int startk = i + 1;
            if (startk == n) {
                startk = 0;
            }
            int endk = startk + ones - 1;
            if (endk < n) {
                intervals.push_back({startk, endk + 1}); // [begin, end)
            } else {
                intervals.push_back({startk, n});
                intervals.push_back({0, endk - n + 1});
            }
        }
        //	sort(intervals.begin(), intervals.end());
        vector<pair<int, int>> timeStamp;
        for (auto &p : intervals) {
            timeStamp.push_back({p.first, 1});
            timeStamp.push_back({p.second, -1});
        }
        sort(timeStamp.begin(), timeStamp.end());
        int k = 0;
        int count = 0;
        int maxCount = 0;
        int resultK = 0;
        for (size_t i = 0; i < timeStamp.size();) {
            if (k >= n)
                break;
            if (k < timeStamp[i].first) {
                k = timeStamp[i].first;
            }
            while (k == timeStamp[i].first) {
                count += timeStamp[i].second;
                i++;
            }
            if (maxCount < count) {
                maxCount = count;
                resultK = k;
            }
            k++;
        }
        return resultK;
    }
};

int main() {

    Solution s;

    return 0;
}
