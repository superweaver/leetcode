#include "common.h"
class Solution {
  public:
    int videoStitching(vector<vector<int>> &clips, int T) {
        if (T == 0)
            return 0;
        sort(clips.begin(), clips.end(), [](const vector<int> &a, const vector<int> &b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            } else {
                return a[1] < b[1];
            }
        });
        // check if we can get [0, T]
        int n = clips.size();
        if (clips[0][0] > 0) {
            return -1;
        }
        int bound = 0;
        int result = 0;
        for (int i = 0; i < n;) {
            if (clips[i][0] > bound) {
                return -1;
            }
            if (clips[i][1] < bound) {
                ++i;
                continue;
            }
            int nextbound = bound;
            int j = i;
            for (; j < n; ++j) {
                if (clips[j][0] > bound) {
                    break;
                } else {
                    nextbound = max(nextbound, clips[j][1]);
                }
            }
            if (nextbound > bound) {
                result++;
            }
            bound = nextbound;
            i = j;
            if (bound >= T) {
                return result;
            }
        }
        return -1;
    }
};

int main() {
	vector<vector<int>> clips = {{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}};
	int T = 10; // r = 3;
	clips = {{0,1},{1,2}};
	T = 5; // -1
	clips = {{0,1},{6,8},{0,2},{5,6},{0,4},{0,3},{6,7},{1,3},{4,7},{1,4},{2,5},{2,6},{3,4},{4,5},{5,7},{6,9}}, T = 9; // 3
	clips = {{0,4},{2,8}}, T = 5; // 2
	clips = {{0,2},{4,8}}, T = 5;




	Solution s;
	cout << s.videoStitching(clips, T) << endl;
	return 0;
}
