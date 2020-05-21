#include "common.h"
// https://leetcode.com/problems/perfect-rectangle/discuss/87180/O(n)-solution-by-counting-corners-with-detailed-explaination
//https://leetcode.com/problems/perfect-rectangle/discuss/87188/O(n-log-n)-sweep-line-solution
class Solution {
public:
    bool isRectangleCover(vector<vector<int> >& rectangles)
    {
        // bounding box
        int left = INT_MAX;
        int bottom = INT_MAX;
        int right = INT_MIN;
        int top = INT_MIN;

        int area = 0;
        unordered_set<string> cache;
        for (auto& v : rectangles) {
            left = min(left, v[0]);
            bottom = min(bottom, v[1]);
            right = max(right, v[2]);
            top = max(top, v[3]);
            string p;
            p = toLongLong(v[0], v[1]);
            handleP(cache, p);
            p = toLongLong(v[0], v[3]);
            handleP(cache, p);
            p = toLongLong(v[2], v[1]);
            handleP(cache, p);
            p = toLongLong(v[2], v[3]);
            handleP(cache, p);
            area += (v[3] - v[1]) * (v[2] - v[0]);
        }
        if (cache.size() == 4) {
            string p;
            p = toLongLong(left, bottom);
            if (cache.find(p) == cache.end()) {
                return false;
            }
            p = toLongLong(left, top);
            if (cache.find(p) == cache.end()) {
                return false;
            }
            p = toLongLong(right, bottom);
            if (cache.find(p) == cache.end()) {
                return false;
            }
            p = toLongLong(right, top);
            if (cache.find(p) == cache.end()) {
                return false;
            }
            return area == (right - left) * (top - bottom);
        }
        return false;
    }

private:
    string toLongLong(int x, int y)
    {
        ostringstream oss;
        oss << x << "," << y;
        return oss.str();
    }
    void handleP(unordered_set<string>& cache, string& p)
    {
        if (cache.find(p) == cache.end()) {
            cache.insert(p);
        } else {
            cache.erase(p);
        }
    }
};



int main() {

	Solution s;

	return 0;
}
